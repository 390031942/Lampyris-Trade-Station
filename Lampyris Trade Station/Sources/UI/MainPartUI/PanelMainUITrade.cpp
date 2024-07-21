/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PanelMainUITrade.h"
#include "Trade/TradeStockSearchLineEdit.h"
#include "Base/CallTimer.h"
#include "Trade/OrderModel.h"
#include "Trade/PositionModel.h"
#include "Trade/AccountSummaryModel.h"
#include "Const/TradeOptionEnum.h"

// QT Include(s)
#include <QValidator>

PanelMainUITrade::PanelMainUITrade(QWidget* parent) 
	: QWidget(parent),
	m_ratioButtonGroup(new QButtonGroup(this)),
	m_orderUnitButtonGroup(new QButtonGroup(this)),
	m_ratio(3),m_quoteUpdateTimerId(-1) {
	this->m_ui.setupUi(this);
	this->createPlaceOrderPartUI();
	this->createOrderPartUI();
	this->createPositionPartUI();
	this->createAccountSummaryPartUI();
}

void PanelMainUITrade::createPlaceOrderPartUI() {
	QObject::connect(this->m_ui.tabTradeDirection, &QTabWidget::currentChanged, [=](int index) {
		if (index == TradeDirection::Buy) {
			this->m_ui.widgetCountInfo->hide();
			this->m_ui.widgetShortable->hide();
		}
		else if (index == TradeDirection::Sell) {
			this->m_ui.widgetCountInfo->show();
			this->m_ui.widgetShortable->show();
		}
	});

	QObject::connect(this->m_ui.buttonReset, &QPushButton::clicked, [=]() {
		this->m_ui.textCode->setText("");
		this->m_ui.widgetBriefQuote->hide();
		this->m_ui.comboBoxOrderType->setEnabled(false);
		this->m_ui.textPrice->setText("");
		this->m_ui.textPrice->setEnabled(false);
		this->m_ui.textCount->setText("1");
		this->m_ui.textCount->setEnabled(false);
		this->m_ui.widgetMoneyCost->hide();
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

	QObject::connect(this->m_ui.textCount, &QLineEdit::textChanged, [=](const QString& text) {
		this->refreshMoneyCost();
	});

	QObject::connect(this->m_ui.textPrice, &QLineEdit::textChanged, [=](const QString& text) {
		this->refreshMoneyCost();
	});

	// Validator设置
	this->m_ui.textCount->setValidator(new QIntValidator(1,9999999,this));
	this->m_ui.textPrice->setValidator(new PriceTextValidator(this));

	// 枚举
	this->m_ui.comboBoxOrderType->setEnum("TradeOrderType");
	this->m_ui.comboBoxExchange->setEnum("TradeExchangeType");
	this->m_ui.comboBoxValidTime->setEnum("TradeTIFType");

	typedef void(QEnumComboBox::* QEnumComboBoxIndexChangedCallback)(int);

	QObject::connect(this->m_ui.comboBoxOrderType, static_cast<QEnumComboBoxIndexChangedCallback>(&QEnumComboBox::currentIndexChanged), [=](int enumValue) {
		TradeOrderType type = static_cast<TradeOrderType>(enumValue);
		if (type == TradeOrderType::Limit) {

		}
		else if (type == TradeOrderType::Limit) {

		}
	});

	QObject::connect(this->m_ui.comboBoxExchange, static_cast<QEnumComboBoxIndexChangedCallback>(&QEnumComboBox::currentIndexChanged), [=](int enumValue) {
		TradeExchangeType type = static_cast<TradeExchangeType>(enumValue);
	});

	QObject::connect(this->m_ui.comboBoxValidTime, static_cast<QEnumComboBoxIndexChangedCallback>(&QEnumComboBox::currentIndexChanged), [=](int enumValue) {
		TradeTIFType type = static_cast<TradeTIFType>(enumValue);
		if (type == TradeTIFType::DAY || type == TradeTIFType::GTC) {
			this->m_ui.widgetTIF->hide();
		}
		else if (type == TradeTIFType::GTC) {
			this->m_ui.widgetTIF->show();
		}
	});

	// 仓位
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtnAll, 0);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn2, 1);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn3, 2);
	this->m_ratioButtonGroup->addButton(this->m_ui.radioBtn4, 3);
	this->m_ui.radioBtn4->setChecked(true);

	typedef void(QButtonGroup::*ButtonClickedCallback)(int);
	QObject::connect(this->m_ratioButtonGroup, static_cast<ButtonClickedCallback>(&QButtonGroup::buttonClicked), [=](int ratio) {
		this->m_ratio = ratio;
	});

	// 数量单位
	this->m_orderUnitButtonGroup->addButton(this->m_ui.radioBtnMoney);
	this->m_orderUnitButtonGroup->addButton(this->m_ui.radioBtnStock);
	this->m_ui.radioBtnStock->setChecked(true);

	// UI默认状态
	this->m_ui.widgetCountInfo->hide();
	this->m_ui.widgetShortable->hide();
	this->m_ui.widgetTIF->hide();
}

void PanelMainUITrade::createOrderPartUI() {
	this->m_ui.tableViewOrder->setModel(new OrderModel(this->m_ui.tableViewOrder));
}

void PanelMainUITrade::createPositionPartUI() {
	this->m_ui.tableViewPosition->setModel(new PositionModel(this->m_ui.tableViewPosition));
}

void PanelMainUITrade::createAccountSummaryPartUI() {
	this->m_ui.listViewAccountSummary->setModel(new AccountSummaryModel(this->m_ui.listViewAccountSummary));
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

void PanelMainUITrade::refreshMoneyCost() {
	double count = this->m_ui.textCount->text().toDouble();
	double price = this->m_ui.textPrice->text().toDouble();
	this->m_ui.textMoneyCost->setText(QString::number(count * price));
}
