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
	 * 连接到IB网关/TWS：
	 * 参数{ip}:IP地址字符串
	 * 参数{port}:端口号
	 * 参数{clientId}:客户端ID，如果有多个客户端连接同一个IB网关/TWS，那么clientId应该互不相同
	 * 返回:是否连接成功
	*/
	bool           connect(const QString& ip,int port,int clientId);
	/*
	 * 中断与IB网关/TWS的连接：
	*/
	void           disconnect();
	/*
	 * 是否与IB网关/TWS连接成功：
	*/
	bool           isConnected();
	/*
	 * 构造函数：
	*/
	               Application();
	/*
	 * 析构函数：
	*/
	virtual       ~Application();
private:
	/*
	 * 从文件中读取程序配置信息：
	*/
	void           readConfigFromFile();

	EWrapper*      m_wrapper;
	EClientSocket* m_clientSocket;
	EReaderSignal* m_signal;
};