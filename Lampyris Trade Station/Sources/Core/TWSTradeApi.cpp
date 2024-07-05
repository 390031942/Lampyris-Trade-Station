/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "TWSTradeApi.h"
#include "TWSEventDispatcher.h"
#include <Core/Application.h>

// TWS Include(s)
#include <TWS/Order.h>
#include <TWS/Contract.h>

void TWSTradeApi::buy(const std::string& code, float price, float count) {
	Contract contract = {};
	contract.symbol = code;
	contract.secType = "STK";
	contract.currency = "USD";
	contract.exchange = "SMART";

	Order order = {};
	order.action = "SELL"; 
	order.totalQuantity = count;

	if (price > 0.0f) {
		order.lmtPrice = price; 
		order.orderType = "LMT";
	}
	else {
		order.orderType = "MKT";
	}

	TWS->placeOrder(this->m_nextValidOrderId, contract, order);
}

void TWSTradeApi::sell(const std::string& code, float price, float count) {
	Contract contract = {};
	contract.symbol = code;
	contract.secType = "STK";
	contract.currency = "USD";
	contract.exchange = "SMART";

	Order order = {};
	order.action = "BUY";
	order.totalQuantity = count;

	if (price > 0.0f) {
		order.lmtPrice = price;
		order.orderType = "LMT";
	}
	else {
		order.orderType = "MKT";
	}

	TWS->placeOrder(this->m_nextValidOrderId, contract, order);
}

void TWSTradeApi::shortBuy(const std::string& code, float price, float count) {

}

void TWSTradeApi::shortSell(const std::string& code, float price, float count) {

}

void TWSTradeApi::cancelOrder() {

}

void TWSTradeApi::queryPosition() {

}

void TWSTradeApi::queryTodayPnl() {

}

void TWSTradeApi::queryTodayOrder() {

}

void TWSTradeApi::queryTodayDealDetail() {

}

void TWSTradeApi::bindEvent() {
	TWSEventBind(TWSEventType::onResNextValidId, [=](OrderId orderId) {
		this->m_nextValidOrderId = orderId;
	});

	TWSEventBind(TWSEventType::onResOpenOrder, [=](OrderId orderId,
		                                           const Contract& contract,
		                                           const Order& order,
		                                           const OrderState& orderState) {

	});

	TWSEventBind(TWSEventType::onResExecDetails, [=](int reqId,
		                                             const Contract& contract, 
		                                             const Execution& execution) {
		
	});

	TWSEventBind(TWSEventType::onResExecDetailsEnd, [=](int reqId) {

	});

	TWSEventBind(TWSEventType::onResOrderStatus, [=](OrderId orderId,
		                                             const std::string& status, 
		                                             Decimal filled,
		                                             Decimal remaining,
		                                             double avgFillPrice, 
		                                             int permId,
		                                             int parentId, 
		                                             double lastFillPrice, 
		                                             int clientId,
		                                             const std::string& whyHeld,
		                                             double mktCapPrice) {
		
	});
}
