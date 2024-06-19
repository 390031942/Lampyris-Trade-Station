/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QTimer>
#include <QString>
#include <QApplication>
#include <QSharedMemory>
#include <QtNetwork/qlocalserver.h>

// TWS API Include(s)
#include <TWS/EWrapper.h>
#include <TWS/EClientSocket.h>
#include <TWS/EReaderOSSignal.h>
#include <TWS/EReader.h>

// Project Include(s)
#include <Base/Singleton.h>

class QWidget;

class Application {
public:
	/*
	 * ���ӵ�IB����/TWS��
	 * ����{ip}:IP��ַ�ַ���
	 * ����{port}:�˿ں�
	 * ����{clientId}:�ͻ���ID������ж���ͻ�������ͬһ��IB����/TWS����ôclientIdӦ�û�����ͬ
	 * ����:�Ƿ����ӳɹ�
	*/
	static bool           connect(const QString& ip,int port,int clientId);
	/*
	 * �ж���IB����/TWS�����ӣ�
	*/
	static void           disconnect();
	/*
	 * �Ƿ���IB����/TWS���ӳɹ���
	*/
	static bool           isConnected();
	/*
	 * �Ƿ���IB����/TWS���ӳɹ���
	*/
	static int            mainLoop();
	/*
	 * ����Ӧ�ó���ʵ�������źţ�
	*/
	static bool           createAppInstanceMutex();
	/*
	 * �ⲿ��ȡTWS API��EClientSocket�������Э�鷢��
	*/
	static EClientSocket* getClientSocket() { return ms_clientSocket; }
	/*
	 * ����TWS API��Ϣ���ն�ʱ�� 
	*/
	static void           startMessageHandler() { ms_reader->start(); ms_twsMsgTimer.start(); }
	/*
	 * ֹͣTWS API��Ϣ���ն�ʱ�� 
	*/
	static void           stopMessageHandler() { ms_twsMsgTimer.stop(); }
	/*
	 * ���캯����
	*/
	                      Application(int argc, char* argv[]);
	/*			         
	 * ����������        
	*/			         
	virtual              ~Application();
private:
	/*
	 * ���ļ��ж�ȡ����������Ϣ��
	*/
	static void           readConfigFromFile();
	/*
	 * TWS API��Ϣ����
	*/
	static void           tickTwsMessage();

	// QT Ӧ�ó������
	static QApplication*  ms_qtApp;

	// TWS API������ض���
	static EWrapper*      ms_wrapper;
	static EClientSocket* ms_clientSocket;
	static EReaderSignal* ms_signal;
	static EReader*       ms_reader;

	// Ӧ��ʵ��������Ϣ��ȷ��ϵͳ��ֻ��һ��ʵ��������
	static QSharedMemory  ms_sharedMemory;
	static QLocalServer   ms_server;
	static QString        ms_uniqueKey;

	// UI��ʾ��Ϣ
	static QWidget*       ms_topWidget;

	// TWS API��Ϣ����ʱ��
	static QTimer         ms_twsMsgTimer;

	/* 
	 *  ��������ʱ�������ֶ�, �����ṩ����ʱ��
	 *  1) IB/TWS ͨ��resCurrentTime���ص�ʱ�������Ϊ׼ȷ������ʱ��
	 *  2) ��׼����ʱ��ʱ��
	*/

	// resCurrentTime���ص�ʱ��
	static QDateTime      ms_serverTime;

	// �յ�resCurrentTimeʱ��ı���ʱ��
	static QDateTime      ms_receivedLocalTime;
};

#ifndef TWS
 #define TWS Application::getClientSocket()
#endif // !TWS