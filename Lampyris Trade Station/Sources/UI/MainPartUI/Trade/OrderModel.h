/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QStandardItemModel>
#include <QStandardItem>

// TWS Include(s)
#include <TWS/Order.h>
#include <TWS/Execution.h>

class OrderModel:public QStandardItemModel {
public:
	enum Tab {
		TodayFilled = 0,
		TodayOrder = 1,
		HistoricalFilled = 2,
		HistoricalOrder = 3, 
	};

				  OrderModel(QObject* parent = nullptr);
	void          setData(const std::vector<Order>& orders);
	void          requestImmediately();
protected:
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};