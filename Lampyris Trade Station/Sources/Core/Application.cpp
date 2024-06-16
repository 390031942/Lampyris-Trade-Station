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

    // ���������ڴ沢�ҳɹ�����ʾ�ǵ�һ��ʵ��
    bool isFirstInstance = ms_sharedMemory.attach() && ms_sharedMemory.create(1);

    // �����ڴ���д������,�������ڵ���ʾ
    if (isFirstInstance) {
        *(static_cast<char*>(ms_sharedMemory.data())) = 1;

        // ������������ʵ������Ϣ
        QLocalServer::removeServer("lampyris_trade_station");
        ms_server.listen("lampyris_trade_station");

        QObject::connect(&ms_server, &QLocalServer::newConnection, [=]() {
            // ���ڵڶ�ʵ����Socket���ӣ����账����Ϣ��������գ�ֱ����ʾ��ǰʵ���Ĵ��ھ���
            QLocalSocket* client = ms_server.nextPendingConnection();
            if (ms_topWidget != nullptr) {
                ms_topWidget->show();
            }
        });

        return true;
    }
    else {
        // ���� ��һ��ʵ����LocalSocket������ɹ����Ӿ��˳���ǰʵ��
        QLocalSocket socket;
        socket.connectToServer("lampyris_trade_station");
        if (socket.waitForConnected(1000)) {
            return false;
        }

        return true;
    }
}

