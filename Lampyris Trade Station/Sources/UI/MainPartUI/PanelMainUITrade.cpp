/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PanelMainUITrade.h"
#include <Base/Localization.h>

PanelMainUITrade::PanelMainUITrade(QWidget* parent) : QWidget(parent) {
	this->m_ui.setupUi(this);
}

void PanelMainUITrade::createPlaceOrderPartUI() {
	QObject::connect(this->m_ui.tabTradeDirection, &QTabWidget::currentChanged, [=](int index) {
		
	});
	this->m_ui.tabTradeDirection->setTabText(0, Localization->get("TradeDirectionBuy"));
	this->m_ui.tabTradeDirection->setTabText(1, Localization->get("TradeDirectionSell"));
}

void PanelMainUITrade::createOrderPartUI() {
}

void PanelMainUITrade::createPositionPartUI() {
}

void PanelMainUITrade::createAccountSummaryPartUI() {
}
