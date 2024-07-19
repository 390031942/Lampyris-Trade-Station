/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ApplicationLifecycle.h"
#include <UI/MainWindow.h>
#include <Core/Application.h>
#include <Model/Quote/QuoteDatabase.h>

#include <Model/Quote/Provider/TWSQuoteProvider.h>
#include <Model/Quote/Provider/EastMoneyQuoteProvider.h>

void ApplicationLifecyle::onLoginSuccess() {
	// 启动TWS 消息监听
	Application::startMessageHandler();

	// 请求IB的服务器时间
	TWSTrade->reqCurrentTime();

	// 设置默认的QuoteProviders
	QuoteDatabase::getInstance()->setIndexBriefQuoteProvider(new EastMoneyIndexBriefQuoteProvider);
	QuoteDatabase::getInstance()->setSnapShotQuoteListProvider(new EastMoneyStockCodeListProvider);
	
	QuoteDatabase::getInstance()->refreshStockList();

	// 打开主窗口
	MainWindow* mainWindow = new MainWindow;
	mainWindow->show();
}

void ApplicationLifecyle::initialize() {

}

void ApplicationLifecyle::finalize() {

}
