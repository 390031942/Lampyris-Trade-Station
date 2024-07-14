/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include "IQuoteProvider.h"
#include <Model/Quote/QuoteDataDef.h>

/*
 * 行情接口-逐笔成交数据：
*/
class ITickByTickQuoteProvider :public IQuoteProvider {
protected:
	typedef std::unordered_map<QString, QuoteBaseDataPtr> QuoteDataMap;
public:
	virtual void subscribeTickByTick(QuoteBaseDataPtr quoteData) = 0;
	virtual void cancelSubscribeTickByTick(QuoteBaseDataPtr quoteData) = 0;
protected:
	QuoteDataMap m_quoteDataMap;
};