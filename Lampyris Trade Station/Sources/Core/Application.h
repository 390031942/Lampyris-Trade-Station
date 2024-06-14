/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>
#include <QApplication>
#include <QSharedMemory>
#include <QtNetwork/qlocalserver.h>

// TWS API Include(s)
#include <TWS/EWrapper.h>
#include <TWS/EClientSocket.h>

// Project Include(s)
#include <Base/Singleton.h>

class QWidget;

class Application:public Singleton<Application> {
public:
	/*
	 * ���ӵ�IB����/TWS��
	 * ����{ip}:IP��ַ�ַ���
	 * ����{port}:�˿ں�
	 * ����{clientId}:�ͻ���ID������ж���ͻ�������ͬһ��IB����/TWS����ôclientIdӦ�û�����ͬ
	 * ����:�Ƿ����ӳɹ�
	*/
	bool           connect(const QString& ip,int port,int clientId);
	/*
	 * �ж���IB����/TWS�����ӣ�
	*/
	void           disconnect();
	/*
	 * �Ƿ���IB����/TWS���ӳɹ���
	*/
	bool           isConnected();
	/*
	 * �Ƿ���IB����/TWS���ӳɹ���
	*/
	int            mainLoop();
	/*
	 * ����Ӧ�ó���ʵ�������źţ�
	*/
	bool           createAppInstanceMutex();
	/*
	 * ���캯����
	*/
	               Application(int argc, char* argv[]);
	/*
	 * ����������
	*/
	virtual       ~Application();
private:
	/*
	 * ���ļ��ж�ȡ����������Ϣ��
	*/
	void           readConfigFromFile();

	// QT Ӧ�ó������
	QApplication   m_qtApp;

	// TWS API������ض���
	EWrapper*      m_wrapper;
	EClientSocket* m_clientSocket;
	EReaderSignal* m_signal;

	// Ӧ��ʵ��������Ϣ��ȷ��ϵͳ��ֻ��һ��ʵ��������
	QSharedMemory  m_sharedMemory;
	QLocalServer   m_server;
	QString        m_uniqueKey;

	// UI��ʾ��Ϣ
	QWidget*       m_topWidget;
};