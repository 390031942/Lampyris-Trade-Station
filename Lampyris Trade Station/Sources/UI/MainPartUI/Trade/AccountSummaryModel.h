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

class AccountSummaryModel :public QStandardItemModel {
public:
	                 AccountSummaryModel(QObject* parent = nullptr);
	void             setAccountSummaryData(const TWSAccountSummaryData& accountsummary);
	void             requestAccountSummaryData();
protected:
	Qt::ItemFlags    flags(const QModelIndex& index) const override;
private:
	void             appendDataRow(const QString& propertyName, const QString& value);
	QStringList      m_header;
	static const int ms_orderColumn;
};