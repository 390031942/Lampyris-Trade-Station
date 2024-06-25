/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "TradeApi.h"
#include <Core/Application.h>
#include <Base/EventDispatcher.h>

// TWS Include(s)
#include <TWS/Order.h>
#include <TWS/Contract.h>

void TradeApi::buy(const std::string& code, float price, float count) {
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

void TradeApi::sell(const std::string& code, float price, float count) {
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

void TradeApi::shortBuy(const std::string& code, float price, float count) {

}

void TradeApi::shortSell(const std::string& code, float price, float count) {

}

void TradeApi::cancelOrder() {

}

void TradeApi::queryPosition() {

}

void TradeApi::queryTodayPnl() {

}

void TradeApi::queryTodayOrder() {

}

void TradeApi::queryTodayDealDetail() {

}

void TradeApi::bindEvent() {
	EventBind(EventType::onResNextValidId, [=](OrderId orderId) {
		this->m_nextValidOrderId = orderId;
	});

	EventBind(EventType::onResOpenOrder, [=](OrderId orderId, 
		                                     const Contract& contract,
		                                     const Order& order,
		                                     const OrderState& orderState) {

	});

	EventBind(EventType::onResExecDetails, [=](int reqId,
		                                       const Contract& contract, 
		                                       const Execution& execution) {
		
	});

	EventBind(EventType::onResExecDetailsEnd, [=](int reqId) {

	});

	EventBind(EventType::onResOrderStatus, [=](OrderId orderId,
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
