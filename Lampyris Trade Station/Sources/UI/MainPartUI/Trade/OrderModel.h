/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

#pragma once

// QT Include(s)
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDate>

// Project Include(s)
#include <Model/TWS/TWSMessageDataDef.h>

class OrderModel:public QStandardItemModel {
public:
	enum Tab {
		ActiveOrder = 0,
		TodayExecution = 1,
		HistoricalOrder = 2, 
		HistoricalExecution = 3,
	};

	enum ExecDirection {
		All = 0,
		Buy = 1,
		Sell = 2,
	};

				     OrderModel(QObject* parent = nullptr);
	void             setOrderData(const std::vector<TWSOrderData>& orders);
	void             setOrderExecutionData(const std::vector<TWSOrderExecutionData>& orderExecutions);
	void             requestImmediately();
	void             switchTab(Tab tab);
	void             requestTabData(Tab tab);
	void             setFilterStartDate(const QDate& date);
	void             setFilterEndDate(const QDate& date);
	void             setFilterStockCode(const QString& code);
	void             setFilterExecDirection(ExecDirection direction);
protected:		     
	Qt::ItemFlags    flags(const QModelIndex& index) const override;
private:		     
	void             requestCurrentTabDataAfterTabChanged();

	Tab              m_curTab;
	QStringList      m_headerOrder;
	QStringList      m_headerOrderExecution;

	static const int ms_orderHeaderColumn;
	static const int ms_orderExecutionHeaderColumn;

	// 历史订单/成交 过滤相关
	QDate            m_fitterStartDate;
	QDate            m_fitterEndDate;
	QString          m_filterStockCode;
	ExecDirection    m_filterExecDirection;
};