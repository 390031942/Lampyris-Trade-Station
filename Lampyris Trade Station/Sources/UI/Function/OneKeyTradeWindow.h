/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QButtonGroup>
#include <QWidget>
#include <QTimer>
#include <QStandardItemModel>
#include <QItemDelegate>

// Project Include(s)
#include <ui_OneKeyTradeWindow.h>

class OneKeyTradeWindow :public QWidget {
	Q_OBJECT
public:
	explicit                   OneKeyTradeWindow(QWidget* parent = NULL);
	virtual                   ~OneKeyTradeWindow();
private:
	void                       OnClickButtonBuy();
	void                       OnClickButtonSell();
	void                       OnClickButtonBuyEmpty();
	void                       OnClickButtonSellEmpty();
	void                       OnClickButtonRefresh();
	void                       OnClickRatioButton(int ratio);
	void                       OnClickAutoSellButton(int mode);
	void                       CaptureStockInfo();
	void                       RefreshStockTradeInfo();
	// void                    RefreshHaltedStockList(std::vector<StockTradeInfo>* list);
	void                       InitHaltedStockTableView();
	void                       InitPreMarketTableView();

	Ui::OneKeyTradeWindow m_ui;
	QButtonGroup               m_buttonGroupRatio;
	QButtonGroup               m_buttonGroupSell;
	QTimer                     m_stockInfoCaptureTimer;
	// StockTradeInfo          m_stockInfo;
	QStandardItemModel*        m_HaltedStockModel;
	QStandardItemModel*        m_preMarketModel;
	int                        m_ratio;
	int                        m_autoSellPercentage;
	int                        m_maxCanBuy{0};
	int                        m_maxCashCanBuy{0};
	double                     m_maxPurchasePower{0.0};
	int                        m_maxSellQty{0};
};
