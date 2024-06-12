/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// TWS API Include(s)
#include "TWS/EWrapper.h"

class MessageWrapper :public EWrapper {
public:
	/*
	 * ��ȡ��һ����Ч�Ķ���ID������placeOrder�Ⱥ�����ʹ��
	*/
	int getNextValid() { 
		return this->m_nextValidId;
	}

	/*
	 * ��Ӧ-��һ����Ч�Ķ���ID��
	 * ����{orderId}:
	*/
	virtual void nextValidId(OrderId orderId) {
		this->m_nextValidId = orderId;
	}

	/*
	 * ��Ӧ-��ǰ������ʱ�䣺
	 * ����{timestamp}:
	*/
	virtual void currentTime(long timestamp) {
		this->m_timestamp = m_timestamp;
	}

	/*
	 * ��Ӧ-��ί�е����飺
	 * ����{orderId}:
	 * ����{contract}:
	 * ����{order}:
	 * ����{orderState}:
	*/
	virtual void openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState) {

	}

	/*
	 * ��Ӧ-�ɽ���ί�е����飺
	 * ����{reqId}:
	 * ����{contract}:
	 * ����{execution}:
	*/
	virtual void execDetails(int reqId, const Contract& contract, const Execution& execution) {

	}

	/*
	 * ��Ӧ����-�ɽ���ί�е����飺
	 * ����{reqId}:
	*/
	virtual void execDetailsEnd(int reqId) {

	}
private:
	// ��һ����Ч�Ķ���ID
	int m_nextValidId;
	// �����ʱ���
	long m_timestamp;
};

