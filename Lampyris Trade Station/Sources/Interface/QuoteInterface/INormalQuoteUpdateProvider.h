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
 * 行情接口-普通行情更新的接口，通常用于 "非毫秒级" 的行情数据更新：
*/
class INormalQuoteUpdateProvider :public IQuoteProvider {
protected:
	typedef std::unordered_map<QString, QuoteBaseDataPtr> QuoteDataMap;
public:
	virtual void subscribeQuoteUpdate(QuoteBaseDataPtr quoteData) = 0;						
	virtual void cancelSubscribeQuoteUpdate(QuoteBaseDataPtr quoteData) = 0;
protected:			 
	QuoteDataMap m_quoteDataMap;
};