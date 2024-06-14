/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Application.h"

// QT Include(s)
#include <QWidget>
#include <QDataStream>
#include <QtNetwork/qlocalsocket.h>

bool Application::connect(const QString& ip, int port, int clientId) {
	if (m_clientSocket == nullptr) {
		return false;
	}
	return m_clientSocket->eConnect(ip.toUtf8().constData(), port, clientId);
}

void Application::disconnect() {
	if (isConnected()) {
		m_clientSocket->eDisconnect();
	}
}

bool Application::isConnected() {
	if (m_clientSocket == nullptr) {
		return false;
	}

	return m_clientSocket->isConnected();
}

int Application::mainLoop() {
	return m_qtApp.exec();
}

Application::Application(int argc, char* argv[]):m_qtApp(argc,argv) {
}

Application::~Application() {
	
}

void Application::readConfigFromFile() {

}

bool Application::createAppInstanceMutex() {
    m_sharedMemory.setKey("lampyris_trade_station");

    // 创建共享内存并且成功，表示是第一个实例
    bool isFirstInstance = m_sharedMemory.attach() && m_sharedMemory.create(1);

    // 向共享内存中写入数据,并处理窗口的显示
    if (isFirstInstance) {
        *(static_cast<char*>(m_sharedMemory.data())) = 1;

        // 监听来自其他实例的消息
        QLocalServer::removeServer("lampyris_trade_station");
        m_server.listen("lampyris_trade_station");

        QObject::connect(&m_server, &QLocalServer::newConnection, [=]() {
            // 对于第二实例的Socket连接，无需处理消息发送与接收，直接显示当前实例的窗口就行
            QLocalSocket* client = m_server.nextPendingConnection();
            if (m_topWidget != nullptr) {
                m_topWidget->show();
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

