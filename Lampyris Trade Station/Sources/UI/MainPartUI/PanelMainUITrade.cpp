/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PanelMainUITrade.h"

PanelMainUITrade::PanelMainUITrade(QWidget* parent) : QWidget(parent) {
	this->m_ui.setupUi(this);
}

void PanelMainUITrade::createPlaceOrderPartUI() {
	QObject::connect(this->m_ui.tabTradeDirection, &QTabWidget::currentChanged, [=](int index) {
		
	});

	QObject::connect(this->m_ui.buttonReset, &QPushButton::clicked, [=]() {
		
	});

	QObject::connect(this->m_ui.buttonEnter, &QPushButton::clicked, [=]() {
		
	});
}

void PanelMainUITrade::createOrderPartUI() {
}

void PanelMainUITrade::createPositionPartUI() {
}

void PanelMainUITrade::createAccountSummaryPartUI() {
}
