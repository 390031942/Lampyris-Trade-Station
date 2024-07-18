/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

#pragma once

// QT Include(s)
#include <QStandardItemModel>
#include <QStandardItem>

// Project Include(s)
#include <Model/TWS/TWSMessageDataDef.h>

class OrderModel:public QStandardItemModel {
public:
	enum Tab {
		TodayFilled = 0,
		TodayOrder = 1,
		HistoricalFilled = 2,
		HistoricalOrder = 3, 
	};

				  OrderModel(QObject* parent = nullptr);
	void          setOrderData(const std::vector<TWSOrderData>& orders);
	void          setOrderExecutionData(const std::vector<TWSOrderExecutionData>& orderExecutions);
	void          requestImmediately();
protected:
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};