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
	// ����IB�ķ�����ʱ��
	// TWSTrade->reqCurrentTime();

	// ����TWS ��Ϣ����
	Application::startMessageHandler();

	// ����Ĭ�ϵ�QuoteProviders
	QuoteDatabase::getInstance()->setIndexBriefQuoteProvider(new EastMoneyIndexBriefQuoteProvider);
	QuoteDatabase::getInstance()->setSnapShotQuoteListProvider(new EastMoneySnapshotQuoteListProvider);
	
	QuoteDatabase::getInstance()->refreshStockList();

	// ��������
	MainWindow* mainWindow = new MainWindow;
	mainWindow->show();
}

void ApplicationLifecyle::initialize() {

}

void ApplicationLifecyle::finalize() {

}
