/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "OrderModel.h"
#include <Base/Localization.h>
#include <Core/TWSEventDispatcher.h>

OrderModel::OrderModel(QObject* parent) : QStandardItemModel(parent) {
	const int columnCount = 11;
	this->setColumnCount(columnCount);

	QStringList headers;
	for (int i = 0; i < columnCount; i++) {
		std::string key = "PanelMainUITrade_Order_" + (i + 1);
		headers << Localization->get(key.c_str());
	}
	this->setHorizontalHeaderLabels(headers);

	TWSEventBind(TWSEventType::onResOpenOrder, [=](const std::vector<TWSOrderData>& data) {
		this->setOrderData(data);
	});

	TWSEventBind(TWSEventType::onResExecDetailsEnd, [=](const std::vector<TWSOrderExecutionData>& data) {
		this->setOrderExecutionData(data);
	});
}

void OrderModel::setOrderData(const std::vector<TWSOrderData>& orders) {
	this->beginResetModel(); // ֪ͨ��ͼģ�ͼ�������

	// �����������
	this->removeRows(0, this->rowCount());

	// ���������
	for (const auto& order : orders) {
		QStandardItem* stockCode = new QStandardItem(QString::fromStdString(order.contract.secId));
		stockCode->setEditable(false);

		QStandardItem* stockName = new QStandardItem(QString::fromStdString(order.contract.symbol));
		stockName->setEditable(false);

		QStandardItem* direction = new QStandardItem(Localization->get(order.isBuy ? "TradeDirectionBuy" : "TradeDirectionSell"));
		direction->setEditable(false);

		QStandardItem* status = new QStandardItem(order.status);
		status->setEditable(false);

		QStandardItem* price = new QStandardItem(QString::number(order.price));
		price->setEditable(false);

		QStandardItem* quantity = new QStandardItem(QString::number(order.count));
		quantity->setEditable(false);

		QStandardItem* executed = new QStandardItem(QString::number(order.filledCount));
		executed->setEditable(false);

		QStandardItem* orderType = new QStandardItem(order.orderType);
		orderType->setEditable(false);

		QStandardItem* currency = new QStandardItem(QString::fromStdString(order.contract.currency));
		currency->setEditable(false);

		QStandardItem* averagePrice = new QStandardItem(QString::number(order.price));
		averagePrice->setEditable(false);

		QStandardItem* orderTime = new QStandardItem(order.timeInForce);
		orderTime->setEditable(false);

		this->appendRow(QList<QStandardItem*>{stockCode, stockName, direction, status, price, quantity, executed, orderType, currency, averagePrice, orderTime});
	}

	this->endResetModel();
}

void OrderModel::setOrderExecutionData(const std::vector<TWSOrderExecutionData>& orderExecutions) {
	this->beginResetModel(); // ֪ͨ��ͼģ�ͼ�������

	// �����������
	this->removeRows(0, this->rowCount());

	// ���������
	for (const auto& order : orders) {
		QStandardItem* stockCode = new QStandardItem(QString::fromStdString(order.contract.secId));
		stockCode->setEditable(false);

		QStandardItem* stockName = new QStandardItem(QString::fromStdString(order.contract.symbol));
		stockName->setEditable(false);

		QStandardItem* direction = new QStandardItem(Localization->get(order.isBuy ? "TradeDirectionBuy" : "TradeDirectionSell"));
		direction->setEditable(false);

		QStandardItem* status = new QStandardItem(order.status);
		status->setEditable(false);

		QStandardItem* price = new QStandardItem(QString::number(order.price));
		price->setEditable(false);

		QStandardItem* quantity = new QStandardItem(QString::number(order.count));
		quantity->setEditable(false);

		QStandardItem* executed = new QStandardItem(QString::number(order.filledCount));
		executed->setEditable(false);

		QStandardItem* orderType = new QStandardItem(order.orderType);
		orderType->setEditable(false);

		QStandardItem* currency = new QStandardItem(QString::fromStdString(order.contract.currency));
		currency->setEditable(false);

		QStandardItem* averagePrice = new QStandardItem(QString::number(order.price));
		averagePrice->setEditable(false);

		QStandardItem* orderTime = new QStandardItem(order.timeInForce);
		orderTime->setEditable(false);

		this->appendRow(QList<QStandardItem*>{stockCode, stockName, direction, status, price, quantity, executed, orderType, currency, averagePrice, orderTime});
	}

	this->endResetModel();
}

void OrderModel::requestImmediately() {

}

Qt::ItemFlags OrderModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
	return defaultFlags & ~Qt::ItemIsEditable; // ���ò��ɱ༭
}
