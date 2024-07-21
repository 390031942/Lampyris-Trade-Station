/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PanelMainUITrade.h"
#include "Trade/TradeStockSearchLineEdit.h"
#include "Base/CallTimer.h"
#include <UI/Common/QGifImage.h>

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

	QObject::connect(this->m_ui.textCode, &TradeStockSearchLineEdit::suggestedTextChanged, [=](const QString& stockCode) {
		this->m_subscribedQuoteData = QuoteDatabase::getInstance()->query(stockCode);
		if (!stockCode.isEmpty()) {
			this->updatgeQuote();
			this->presetOrderData();
			this->startQuoteUpdateTimer();
		}
		else {
			this->stopQuoteUpdateTimer();
		}
	});

	// Ã¶¾Ù
	this->m_ui.comboBoxOrderType->setEnum("TradeOrderType");
	this->m_ui.comboBoxExchange->setEnum("TradeExchangeType");
	this->m_ui.comboBoxValidTime->setEnum("TradeTIFType");
	QObject::connect(this->m_ui.comboBoxOrderType, &QComboBox::currentTextChanged, [=]() {
		
	});

	// ²ÖÎ»
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtnAll, 0);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn2, 1);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn3, 2);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn4, 3);

	typedef void(QButtonGroup::*ButtonClickedCallback)(int);
	QObject::connect(this->m_ratioButtonGroup, static_cast<ButtonClickedCallback>(&QButtonGroup::buttonClicked), [=](int ratio) {
		this->m_ratio = ratio;
	});
}

void PanelMainUITrade::createOrderPartUI() {
}

void PanelMainUITrade::createPositionPartUI() {
}

void PanelMainUITrade::createAccountSummaryPartUI() {
}

void PanelMainUITrade::startQuoteUpdateTimer() {
	m_quoteUpdateTimerId = CallTimer::getInstance()->setInterval([=]() {
		this->updatgeQuote();
	}, 1000);
}

void PanelMainUITrade::stopQuoteUpdateTimer() {
	if (m_quoteUpdateTimerId > 0) {
		CallTimer::getInstance()->clearTimer(m_quoteUpdateTimerId);
		m_quoteUpdateTimerId = -1;
	}
}

void PanelMainUITrade::updatgeQuote() {
	const auto realTimeData = this->m_subscribedQuoteData->realTimeData();

	QString displayText = QString("%1 %2 %3%%")
		.arg(realTimeData->getPrice())
		.arg(realTimeData->getChange())
		.arg(realTimeData->getChangePercentage());

	this->m_ui.textBriefQuote->setText(displayText);
}

void PanelMainUITrade::presetOrderData() {
	this->m_ui.textCount->setText("1");
	this->m_ui.radioBtn4->setChecked(true);
	this->m_ui.comboBoxExchange->setCurrentIndex("SMART");
}
