/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// TWS API Include(s)
#include <TWS/EWrapper.h>
#include <TWS/EClientSocket.h>

// Project Include(s)
#include <Base/Singleton.h>

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
	 * ���캯����
	*/
	               Application();
	/*
	 * ����������
	*/
	virtual       ~Application();
private:
	/*
	 * ���ļ��ж�ȡ����������Ϣ��
	*/
	void           readConfigFromFile();

	EWrapper*      m_wrapper;
	EClientSocket* m_clientSocket;
	EReaderSignal* m_signal;
};