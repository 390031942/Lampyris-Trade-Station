/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "OrderModel.h"
#include <Base/Localization.h>
#include <Core/TWSEventDispatcher.h>
#include <Core/Application.h>

const int OrderModel::ms_orderHeaderColumn = 11;
const int OrderModel::ms_orderExecutionHeaderColumn = 8;

OrderModel::OrderModel(QObject* parent) : QStandardItemModel(parent) {
	for (int i = 0; i < ms_orderHeaderColumn; i++) {
		std::string key = "PanelMainUITrade_Order_" + (i + 1);
		m_headerOrder << Localization->get(key.c_str());
	}

	for (int i = 0; i < ms_orderExecutionHeaderColumn; i++) {
		std::string key = "PanelMainUITrade_OrderExecution_" + (i + 1);
		m_headerOrderExecution << Localization->get(key.c_str());
	}

	TWSEventBind(TWSEventType::onResOpenOrder, [=](const std::vector<TWSOrderData>& data) {
		this->setOrderData(data);
	});

	TWSEventBind(TWSEventType::onResExecDetailsEnd, [=](const std::vector<TWSOrderExecutionData>& data) {
		this->setOrderExecutionData(data);
	});

	this->switchTab(Tab::ActiveOrder);
}

void OrderModel::setOrderData(const std::vector<TWSOrderData>& orders) {
	this->beginResetModel(); // 通知视图模型即将重置

	// 清空现有数据
	this->removeRows(0, this->rowCount());

	// 添加新数据
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
	this->beginResetModel(); // 通知视图模型即将重置

	// 清空现有数据
	this->removeRows(0, this->rowCount());

	// 添加新数据
	for (const auto& orderExec : orderExecutions) {
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

void OrderModel::switchTab(Tab tab) {
	if (tab == Tab::ActiveOrder || tab == Tab::HistoricalOrder) {
		this->setHorizontalHeaderLabels(m_headerOrder);
	}
	else if (tab == Tab::TodayExecution || tab == Tab::HistoricalExecution) {
		this->setHorizontalHeaderLabels(m_headerOrderExecution);
	}

	this->requestTabData(tab);
}

void OrderModel::requestTabData(Tab tab) {
	switch (tab) {
		case Tab::ActiveOrder:
			TWSQuote->reqAllOpenOrders();
			break;
		case Tab::HistoricalOrder:
			TWSQuote->reqCompletedOrders(true);
			break;
		case Tab::TodayExecution:
		case Tab::HistoricalExecution:
			auto execFilter = ExecutionFilter();

			if (!m_filterStockCode.isEmpty()) {
				execFilter.m_symbol = m_filterStockCode.toUtf8();
			}

			if (!m_fitterStartDate.isNull()) {
				execFilter.m_time = m_fitterStartDate.toString("yyyyMMdd hh:mm:ss").toUtf8();
			}

			if(!m_filterExecDirection != ExecDirection::All) {
				execFilter.m_side = m_filterExecDirection == ExecDirection::Buy ? "BUY" : "SELL";
			}

			TWSQuote->reqExecutions(Application::getNextRequestId(), execFilter);
			break;
	}
}

void OrderModel::requestCurrentTabDataAfterTabChanged() {
	if (this->m_curTab == Tab::ActiveOrder)
		return;

	this->requestTabData(this->m_curTab);
}

void OrderModel::setFilterStartDate(const QDate& date) {
	if (this->m_fitterStartDate != date) {
		this->m_fitterStartDate = date;
		this->requestCurrentTabDataAfterTabChanged();
	}
}

void OrderModel::setFilterEndDate(const QDate& date) {
	if (this->m_fitterEndDate != date) {
		this->m_fitterEndDate = date;
	}
}

void OrderModel::setFilterStockCode(const QString& code) {
	if (this->m_filterStockCode != code) {
		this->m_filterStockCode = code;
	}
}

void OrderModel::setFilterExecDirection(ExecDirection direction) {
	if (this->m_filterExecDirection != direction) {
		this->m_filterExecDirection = direction;
		this->requestCurrentTabDataAfterTabChanged();
	}
}

Qt::ItemFlags OrderModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
	return defaultFlags & ~Qt::ItemIsEditable; // 设置不可编辑
}
