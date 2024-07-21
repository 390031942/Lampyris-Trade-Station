/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QButtonGroup>

// Project Include(s)
#include <ui_PanelMainUITrade.h>
#include <Model/Quote/QuoteDatabase.h>

class PanelMainUITrade : public QWidget {
    Q_OBJECT
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
	int                     m_quoteUpdateTimerId;
	QuoteDataReader         m_subscribedQuoteData;
	int                     m_ratio;

    Ui::PanelMainUITrade    m_ui;
	QButtonGroup*           m_ratioButtonGroup;
};