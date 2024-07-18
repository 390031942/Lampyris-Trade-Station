/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "AccountSummaryModel.h"
#include <Base/Localization.h>
#include <Core/TWSEventDispatcher.h>
#include <Core/Application.h>

AccountSummaryModel::AccountSummaryModel(QObject* parent) {
	TWSEventBind(TWSEventType::onResAccountSummary, [=](const TWSAccountSummaryData& accountsummary) {
		this->setAccountSummaryData(accountsummary);
	});
}

void AccountSummaryModel::setAccountSummaryData(const TWSAccountSummaryData& accountsummary) {
	this->beginResetModel(); // 通知视图模型即将重置

	// 清空现有数据
	this->removeRows(0, this->rowCount());

	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_1"), accountsummary.netLiquidation);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_2"), accountsummary.grossPositionValue);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_3"), accountsummary.availableFunds);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_4"), accountsummary.buyingPower);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_5"), accountsummary.leverage);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_6"), accountsummary.initMarginReq);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_7"), accountsummary.maintMarginReq);
	this->appendDataRow(Localization->get("PanelMainUITrade_AccountSummary_8"), accountsummary.dayTradesRemaining);

	this->endResetModel();
}

void AccountSummaryModel::requestAccountSummaryData() {
}

Qt::ItemFlags AccountSummaryModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
	return defaultFlags & ~Qt::ItemIsEditable; // 设置不可编辑
}

void AccountSummaryModel::appendDataRow(const QString& propertyName, const QString& value) {
	QStandardItem* rowNameItem = new QStandardItem(propertyName);
	rowNameItem->setEditable(false);

	QStandardItem* valueItem = new QStandardItem(value);
	valueItem->setEditable(false);

	this->appendRow(QList<QStandardItem*>{rowNameItem, valueItem});
}
