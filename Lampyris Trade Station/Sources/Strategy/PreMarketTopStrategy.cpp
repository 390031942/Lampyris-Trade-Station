/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PreMarketTopStrategy.h"
#include <Model/Quote/QuoteDatabase.h>

LAMPYRIS_STRATEGY_IMPL(
	PreMarketTopStrategy,
	"盘前龙一模型",
	"Rickeeer & MaintainFly",
	"盘前龙一模型是一种利用盘前结束时，涨幅榜首的股的活跃程度，实现快速且稳定盈利的模型,"
	"该模型在标的开盘剧烈震荡时,以开盘价*(1-X%)的价位买入，并以买入价*(1+Y%)的价格卖出。"
);


bool PreMarketTopStrategy::executeCondition() {
	return false;
}

bool PreMarketTopStrategy::tick() {
	auto codeList = QuoteDatabase::getInstance()->getScannerResult(QuoteDatabase::BuildInScannerType::PreMarketTopGainer);
	auto contract = codeList.size() > 0 ? codeList[0] : Contract();

	QuoteBaseDataPtr quoteData = QuoteDatabase::getInstance()->query(contract.secId.c_str());
	const TickByTickData* tickByTickData = quoteData->realTimeData()->getLastTickByTick();
	float price = tickByTickData->price;

	return false;
}
