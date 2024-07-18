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

class PositionModel :public QStandardItemModel {
public:
	                 PositionModel(QObject* parent = nullptr);
	void             setPositionData(const std::vector<TWSPositionData>& orders);
protected:		     
	Qt::ItemFlags    flags(const QModelIndex& index) const override;
private:
	QStringList      m_header;
	static const int ms_orderColumn;
};