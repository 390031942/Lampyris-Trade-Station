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
 * TWS账户资产信息
*/
struct TWSAccountSummary {
	// 总资产
	float netLiquidation;
	// 持仓市值
	float grossPositionValue;
	// 可用资金
	float availableFunds;
	// 购买力
	float buyingPower;
	// 杠杆值
	float leverage;
	// 总计初始保证金要求
	float initMarginReq;
	// 总计维持保证金要求
	float maintMarginReq;
	// 日内剩余交易次数, -1表示无限制
	int dayTradesRemaining;
};

/*
 * TWS账户持仓信息
*/
struct TWSPositionData {
	// 持仓数量
	float count;
	// 成本均价
	float avgCost;
	// 今日盈亏
	float dailyPnL;
	// 未实现盈亏
	float unrealizedPnL;
	// 已实现盈亏
	float realizedPnL;
};

/*
 * TWS账户委托订单信息
*/
struct TWSOrderData {
	// 合约
	Contract    contract;
	// 订单ID
	OrderId     orderId;
	// 委托方向
	bool        isBuy;
	// 委托价格
	float       price;
	// 状态
	QString     status;
	// 委托数量
	int         count;
	// 成交数量
	int         filledCount;
	// 订单类型
	QString     orderType;
	// 有效期
	QString     timeInForce;
};

/*
 * TWS账户委托订单成交信息
*/
struct TWSOrderExecutionData {
	// 合约
	Contract    contract;
	// 订单ID
	OrderId     orderId;
	// 执行时间
	QString     executionTime;
	// 价格
	float       price;
	// 数量
	int         count;
	// 委托方向
	bool        isBuy;
};