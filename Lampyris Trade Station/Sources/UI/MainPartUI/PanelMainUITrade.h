/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QValidator>

// Project Include(s)
#include <ui_PanelMainUITrade.h>
#include <Model/Quote/QuoteDatabase.h>

class PriceTextValidator : public QValidator {
public:
    explicit PriceTextValidator(QObject* parent = nullptr) : QValidator(parent) {}

    virtual State validate(QString& input, int& pos) const override {
        Q_UNUSED(pos)

        // 清除输入中的非法字符
        input.remove(QRegExp("[^0-9.]"));

        // 检查是否为非负数
        bool ok;
        double value = input.toDouble(&ok);
        if (!ok || value < 0) {
            return Invalid;
        }

        if (value > 1) {
            input = QLocale().toString(value, 'f', 2);
        }
        else {
            input = QLocale().toString(value, 'f', 4);
        }

        return Acceptable;
    }

    virtual void fixup(QString& input) const override {
        int pos = 0;
        State state = validate(input, pos);
        if (state == Acceptable) {
            input = input.trimmed();
        }
    }
};

class PanelMainUITrade : public QWidget {
    Q_OBJECT
    enum TradeDirection{ Buy = 0, Sell = 1};
public:
    explicit                PanelMainUITrade(QWidget* parent = nullptr);
private:				    
	void                    createPlaceOrderPartUI();
	void                    createOrderPartUI();
	void                    createPositionPartUI();
	void                    createAccountSummaryPartUI();
						    
	void                    startQuoteUpdateTimer();
	void                    stopQuoteUpdateTimer();
	void                    updatgeQuote();
	void                    presetOrderData();
    void                    refreshMoneyCost();

	int                     m_quoteUpdateTimerId;
	QuoteDataReader         m_subscribedQuoteData;
	int                     m_ratio;

    Ui::PanelMainUITrade    m_ui;
	QButtonGroup*           m_ratioButtonGroup;
	QButtonGroup*           m_orderUnitButtonGroup;
};