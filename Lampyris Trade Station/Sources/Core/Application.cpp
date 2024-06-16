/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Application.h"

// QT Include(s)
#include <QWidget>
#include <QDataStream>
#include <QtNetwork/qlocalsocket.h>
#include <Utility/MemoryUtil.h>
#include <Core/MessageWrapper.h>

QApplication*  Application::ms_qtApp;
EWrapper*      Application::ms_wrapper;
EClientSocket* Application::ms_clientSocket;
EReaderSignal* Application::ms_signal;
EReader*       Application::ms_reader;
QSharedMemory  Application::ms_sharedMemory;
QLocalServer   Application::ms_server;
QString        Application::ms_uniqueKey;
QWidget*       Application::ms_topWidget;

bool Application::connect(const QString& ip, int port, int clientId) {
	if (ms_clientSocket == nullptr) {
		return false;
	}
	return ms_clientSocket->eConnect(ip.toUtf8().constData(), port, clientId);
}

void Application::disconnect() {
	if (isConnected()) {
		ms_clientSocket->eDisconnect();
	}
}

bool Application::isConnected() {
	if (ms_clientSocket == nullptr) {
		return false;
	}

	return ms_clientSocket->isConnected();
}

int Application::mainLoop() {
	return ms_qtApp->exec();
}

Application::Application(int argc, char* argv[]) {
    ms_qtApp = new QApplication(argc, argv);

    // TWS initialize
    ms_wrapper = new MessageWrapper();
    ms_signal = new EReaderOSSignal();
    ms_clientSocket = new EClientSocket(ms_wrapper, ms_signal);
    ms_reader = new EReader(ms_clientSocket, ms_signal);
}

Application::~Application() {
    LAMPYRIS_SAFE_DELETE(ms_qtApp);
}

void Application::readConfigFromFile() {

}

bool Application::createAppInstanceMutex() {
    ms_sharedMemory.setKey("lampyris_trade_station");

    // 创建共享内存并且成功，表示是第一个实例
    bool isFirstInstance = ms_sharedMemory.attach() && ms_sharedMemory.create(1);

    // 向共享内存中写入数据,并处理窗口的显示
    if (isFirstInstance) {
        *(static_cast<char*>(ms_sharedMemory.data())) = 1;

        // 监听来自其他实例的消息
        QLocalServer::removeServer("lampyris_trade_station");
        ms_server.listen("lampyris_trade_station");

        QObject::connect(&ms_server, &QLocalServer::newConnection, [=]() {
            // 对于第二实例的Socket连接，无需处理消息发送与接收，直接显示当前实例的窗口就行
            QLocalSocket* client = ms_server.nextPendingConnection();
            if (ms_topWidget != nullptr) {
                ms_topWidget->show();
            }
        });

        return true;
    }
    else {
        // 连接 第一个实例的LocalSocket，如果成功连接就退出当前实例
        QLocalSocket socket;
        socket.connectToServer("lampyris_trade_station");
        if (socket.waitForConnected(1000)) {
            return false;
        }

        return true;
    }
}

