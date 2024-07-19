/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "PositionModel.h"
#include <Base/Localization.h>
#include <Core/TWSEventDispatcher.h>
#include <Core/Application.h>

const int PositionModel::ms_orderColumn = 9;

PositionModel::PositionModel(QObject* parent) {
	for (int i = 0; i < ms_orderColumn; i++) {
		std::string key = "PanelMainUITrade_Position_" + (i + 1);
		m_header << Localization->get(key.c_str());
	}

	this->setHorizontalHeaderLabels(m_header);

	TWSEventBind(TWSEventType::onResPosition, [=](const std::vector<TWSPositionData>& data) {
		this->setPositionData(data);
	});
}

void PositionModel::setPositionData(const std::vector<TWSPositionData>& positions) {
	this->beginResetModel(); // 通知视图模型即将重置

	// 清空现有数据
	this->removeRows(0, this->rowCount());

	// 添加新数据
	for (const auto& position : positions) {
		QStandardItem* stockCode = new QStandardItem(QString::fromStdString(position.contract.secId));
		stockCode->setEditable(false);

		QStandardItem* stockName = new QStandardItem(QString::fromStdString(position.contract.symbol));
		stockName->setEditable(false);

		QStandardItem* count = new QStandardItem(QString::number(position.count));
		count->setEditable(false);

		QStandardItem* priceCost = new QStandardItem(QString::number(position.avgCost));
		priceCost->setEditable(false);

		QStandardItem* money = new QStandardItem("0.00");
		money->setEditable(false);

		QStandardItem* todayPnlMoney = new QStandardItem(QString::number(position.dailyPnL));
		todayPnlMoney->setEditable(false);

		QStandardItem* todayPnlPercentage = new QStandardItem(QString::number(position.dailyPnL / (position.count * position.avgCost)));
		todayPnlPercentage->setEditable(false);

		QStandardItem* totalPnlMoney = new QStandardItem(QString::number(position.unrealizedPnL));
		todayPnlMoney->setEditable(false);
		
		QStandardItem* totalPnlPercentage = new QStandardItem(QString::number(position.unrealizedPnL / (position.count * position.avgCost)));
		todayPnlPercentage->setEditable(false);

		this->appendRow(QList<QStandardItem*>{stockCode, stockName, count, priceCost, money});
	}

	this->endResetModel();
}

Qt::ItemFlags PositionModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
	return defaultFlags & ~Qt::ItemIsEditable; // 设置不可编辑
}
