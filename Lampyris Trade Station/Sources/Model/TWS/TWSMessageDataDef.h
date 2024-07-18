/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// TWS Include(s)
#include <TWS/Order.h>
#include <TWS/Contract.h>
#include <TWS/Execution.h>

#ifndef LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET
#define LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET(dataKeeper) \
	if (dataKeeper.ready) { dataKeeper.ready = false; dataKeeper.data.clear(); }
#endif // !LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET

template<typename T>
struct TWSDataListKepper {
	bool ready;
	std::vector<T> data;
};

/*
 * TWS�˻��ʲ���Ϣ
*/
struct TWSAccountSummaryData {
	// ���ʲ�
	QString netLiquidation;
	// �ֲ���ֵ
	QString grossPositionValue;
	// �����ʽ�
	QString availableFunds;
	// ������
	QString buyingPower;
	// �ܸ�ֵ
	QString leverage;
	// �ܼƳ�ʼ��֤��Ҫ��
	QString initMarginReq;
	// �ܼ�ά�ֱ�֤��Ҫ��
	QString maintMarginReq;
	// ����ʣ�ཻ�״���, -1��ʾ������
	QString dayTradesRemaining;
};

/*
 * TWS�˻��ֲ���Ϣ
*/
struct TWSPositionData {
	// ��Լ
	Contract contract;
	// �ֲ�����
	float count;
	// �ɱ�����
	float avgCost;
	// ����ӯ��
	float dailyPnL;
	// δʵ��ӯ��
	float unrealizedPnL;
	// ��ʵ��ӯ��
	float realizedPnL;
	// �г���(����)
	float marketPrice;
};

/*
 * TWS�˻�ί�ж�����Ϣ
*/
struct TWSOrderData {
	// ��Լ
	Contract    contract;
	// ����ID
	OrderId     orderId;
	// ί�з���
	bool        isBuy;
	// ί�м۸�
	float       price;
	// ״̬
	QString     status;
	// ί������
	int         count;
	// �ɽ�����
	int         filledCount;
	// ��������
	QString     orderType;
	// ��Ч��
	QString     timeInForce;
};

/*
 * TWS�˻�ί�ж����ɽ���Ϣ
*/
struct TWSOrderExecutionData {
	// ��Լ
	Contract    contract;
	// ����ID
	OrderId     orderId;
	// ִ��ʱ��
	QString     executionTime;
	// �۸�
	float       price;
	// ����
	int         count;
	// ί�з���
	bool        isBuy;
	// Ӷ��
	float       commission;
};