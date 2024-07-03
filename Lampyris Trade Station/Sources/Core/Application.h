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
#include <Const/ConnectState.h>

#ifndef LTS_COMPILE_TIME
#define LTS_COMPILE_TIME __DATE__ " " __TIME__
#endif // !LTS_COMPILE_TIME

#ifndef TWS
#define TWS Application::getClientSocket()
#endif // !TWS

class QWidget;

typedef std::function<void()> TickFunc;
typedef std::vector<TickFunc> TickFuncList;

class Application {
public:
	/*
	 * 连接到IB网关/TWS：
	 * 参数{ip}:IP地址字符串
	 * 参数{port}:端口号
	 * 参数{clientId}:客户端ID，如果有多个客户端连接同一个IB网关/TWS，那么clientId应该互不相同
	 * 返回:是否连接成功
	*/
	static bool           connect(const QString& ip,int port,int clientId);
	/*
	 * 中断与IB网关/TWS的连接：
	*/
	static void           disconnect();
	/*
	 * 与IB网关/TWS连接状态：
	*/
	static ConnectState   connectState();
	/*
	 * 是否与IB网关/TWS连接成功：
	*/
	static int            mainLoop();
	/*
	 * 创建应用程序实例互斥信号：
	*/
	static bool           createAppInstanceMutex();
	/*
	 * 获取应用程序名称字符串：
	*/
	static QString        getAppName();
	/*
	 * 获取应用程序名称版本名称：
	*/
	static QString        getVersion();
	/*
	 * 设置应用程序图标：
	*/
	static void           setAppIcon(const QIcon& icon);
	/*
	 * 外部获取TWS API的EClientSocket对象进行协议发送
	*/
	static EClientSocket* getClientSocket() { return ms_clientSocket; }
	/*
	 * 开启TWS API消息接收定时器 
	*/
	static void           startMessageHandler() { ms_reader->start(); ms_tickTimer.start(); }
	/*
	 * 停止TWS API消息接收定时器 
	*/
	static void           stopMessageHandler() { ms_tickTimer.stop(); }
	/*
	 * 添加 Tick事件：
	*/
	static void           addTickFunc(TickFunc func);
	/*
	 * 构造函数：
	*/
	                      Application(int argc, char* argv[]);
	/*			         
	 * 析构函数：        
	*/			         
	virtual              ~Application();
private:
	/*
	 * 从文件中读取程序配置信息：
	*/
	static void           readConfigFromFile();
	/*
	 * TWS API消息处理：
	*/
	static void           tickTwsMessage();

	// QT 应用程序对象
	static QApplication*  ms_qtApp;

	// TWS API连接相关对象
	static EWrapper*      ms_wrapper;
	static EClientSocket* ms_clientSocket;
	static EReaderSignal* ms_signal;
	static EReader*       ms_reader;

	// 应用实例互斥信息，确保系统下只有一个实例在运行
	static QSharedMemory  ms_sharedMemory;
	static QLocalServer   ms_server;
	static QString        ms_uniqueKey;

	// UI显示信息
	static QWidget*       ms_topWidget;

	// TWS API消息处理定时器
	static QTimer         ms_tickTimer;

	/* 
	 *  程序启动时间戳相关字段, 这里提供两种时间
	 *  1) IB/TWS 通过resCurrentTime返回的时间戳，作为准确的美东时间
	 *  2) 标准北京时间时间
	*/

	// resCurrentTime返回的时间
	static QDateTime      ms_serverTime;

	// 收到resCurrentTime时候的本地时间
	static QDateTime      ms_receivedLocalTime;

	// 需要被Tick的函数
	static TickFuncList   ms_tickFuncList;
};