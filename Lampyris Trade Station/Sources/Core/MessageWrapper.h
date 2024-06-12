/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// TWS API Include(s)
#include "TWS/EWrapper.h"

class MessageWrapper :public EWrapper {
public:
	/*
	 * 获取下一个有效的订单ID，其在placeOrder等函数中使用
	*/
	int getNextValid() { 
		return this->m_nextValidId;
	}

	/*
	 * 响应-下一个有效的订单ID：
	 * 参数{orderId}:
	*/
	virtual void nextValidId(OrderId orderId) {
		this->m_nextValidId = orderId;
	}

	/*
	 * 响应-当前服务器时间：
	 * 参数{timestamp}:
	*/
	virtual void currentTime(long timestamp) {
		this->m_timestamp = m_timestamp;
	}

	/*
	 * 响应-新委托单详情：
	 * 参数{orderId}:
	 * 参数{contract}:
	 * 参数{order}:
	 * 参数{orderState}:
	*/
	virtual void openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState) {

	}

	/*
	 * 响应-成交的委托单详情：
	 * 参数{reqId}:
	 * 参数{contract}:
	 * 参数{execution}:
	*/
	virtual void execDetails(int reqId, const Contract& contract, const Execution& execution) {

	}

	/*
	 * 响应结束-成交的委托单详情：
	 * 参数{reqId}:
	*/
	virtual void execDetailsEnd(int reqId) {

	}
private:
	// 下一个有效的订单ID
	int m_nextValidId;
	// 服务端时间戳
	long m_timestamp;
};

