/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PreMarketTopStrategy.h"
#include <Model/Quote/QuoteDatabase.h>

LAMPYRIS_STRATEGY_IMPL(
	PreMarketTopStrategy,
	"��ǰ��һģ��",
	"Rickeeer & MaintainFly",
	"��ǰ��һģ����һ��������ǰ����ʱ���Ƿ����׵ĹɵĻ�Ծ�̶ȣ�ʵ�ֿ������ȶ�ӯ����ģ��,"
	"��ģ���ڱ�Ŀ��̾�����ʱ,�Կ��̼�*(1-X%)�ļ�λ���룬���������*(1+Y%)�ļ۸�������"
);


bool PreMarketTopStrategy::executeCondition() {
	
}

bool PreMarketTopStrategy::tick() {
	auto codeList = QuoteDatabase::getInstance()->getScannerResult(QuoteDatabase::BuildInScannerType::PreMarketMostActive);
	auto code = codeList.size() > 0 ? codeList[0] : "";

	QuoteBaseDataPtr quoteData = QuoteDatabase::getInstance()->query(code);
	TickByTickData tickByTickData = quoteData->realTimeData()->getLastTickByTick();
	float price = tickByTickData.price;
}
