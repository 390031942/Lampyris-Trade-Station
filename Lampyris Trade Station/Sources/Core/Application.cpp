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

    // ���������ڴ沢�ҳɹ�����ʾ�ǵ�һ��ʵ��
    bool isFirstInstance = m_sharedMemory.attach() && m_sharedMemory.create(1);

    // �����ڴ���д������,�������ڵ���ʾ
    if (isFirstInstance) {
        *(static_cast<char*>(m_sharedMemory.data())) = 1;

        // ������������ʵ������Ϣ
        QLocalServer::removeServer("lampyris_trade_station");
        m_server.listen("lampyris_trade_station");

        QObject::connect(&m_server, &QLocalServer::newConnection, [=]() {
            // ���ڵڶ�ʵ����Socket���ӣ����账����Ϣ��������գ�ֱ����ʾ��ǰʵ���Ĵ��ھ���
            QLocalSocket* client = m_server.nextPendingConnection();
            if (m_topWidget != nullptr) {
                m_topWidget->show();
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

