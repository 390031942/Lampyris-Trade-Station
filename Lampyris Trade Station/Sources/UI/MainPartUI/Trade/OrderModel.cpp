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

	TWSEventBind(TWSEventType::onResOpenOrder)
}

void OrderModel::setData(const std::vector<Order>& orders) {
	this->beginResetModel(); // ֪ͨ��ͼģ�ͼ�������

	// �����������
	this->removeRows(0, this->rowCount());

	// ���������
	for (const auto& order : orders) {
		QStandardItem* stockCode = new QStandardItem(QString::fromStdString(order.symbol));
		stockCode->setEditable(false);

		QStandardItem* stockName = new QStandardItem(QString::fromStdString(order.localSymbol));
		stockName->setEditable(false);

		QStandardItem* direction = new QStandardItem(QString::fromStdString(order.action));
		direction->setEditable(false);

		QStandardItem* status = new QStandardItem(QString::fromStdString(order.status));
		status->setEditable(false);

		QStandardItem* price = new QStandardItem(QString::number(order.lmtPrice));
		price->setEditable(false);

		QStandardItem* quantity = new QStandardItem(QString::number(order.totalQuantity));
		quantity->setEditable(false);

		QStandardItem* executed = new QStandardItem(QString::number(order.filledQuantity));
		executed->setEditable(false);

		QStandardItem* orderType = new QStandardItem(QString::fromStdString(order.orderType));
		orderType->setEditable(false);

		QStandardItem* currency = new QStandardItem(QString::fromStdString(order.currency));
		currency->setEditable(false);

		QStandardItem* averagePrice = new QStandardItem(QString::number(order.price));
		averagePrice->setEditable(false);

		QStandardItem* orderTime = new QStandardItem(QString::fromStdString(order.completedTime));
		orderTime->setEditable(false);

		// ����������ӵ�ģ����
		appendRow(QList<QStandardItem*>{stockCode, stockName, direction, status, price, quantity, executed, orderType, currency, averagePrice, orderTime});
	}
	endResetModel(); // ֪ͨ��ͼģ���������
}

void OrderModel::requestImmediately() {

}

Qt::ItemFlags OrderModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
	return defaultFlags & ~Qt::ItemIsEditable; // ���ò��ɱ༭
}
