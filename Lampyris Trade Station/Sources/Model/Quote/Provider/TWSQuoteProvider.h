/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Core/TWSEventDispatcher.h>
#include <Interface/QuoteInterface/ITickByTickQuoteProvider.h>
#include <Interface/QuoteInterface/INormalQuoteUpdateProvider.h>

// STD Include(s)
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace Detailed {
class TWSQuoteProvider:public Singleton<TWSQuoteProvider> {
public:
	void subscribeQuoteUpdate(QuoteBaseDataPtr quoteData);
	void subscribeTickByTick(QuoteBaseDataPtr quoteData);
	void cancelSubscribeQuoteUpdate(QuoteBaseDataPtr quoteData);
	void cancelSubscribeTickByTick(QuoteBaseDataPtr quoteData);

  	     TWSQuoteProvider();
	    ~TWSQuoteProvider();
private:
	void bindEvent();
	
	int m_tickerIdAutoIncrement = 0;
	int m_scannerTickerId = -1;
	int m_scannerReqId = -1;

	std::unordered_map<int,QuoteBaseDataPtr> m_tickerId2DataMap;
	std::vector<ContractDetails> m_scannerResult;
};
} // end of namespace 'Detailed'

class TWSNormalQuoteUpdateProvider:public INormalQuoteUpdateProvider {
public:
	virtual void subscribeQuoteUpdate(QuoteBaseDataPtr quoteData) override {
		Detailed::TWSQuoteProvider::getInstance()->subscribeQuoteUpdate(quoteData);
	}
	virtual void cancelSubscribeQuoteUpdate(QuoteBaseDataPtr quoteData) override {
		Detailed::TWSQuoteProvider::getInstance()->cancelSubscribeQuoteUpdate(quoteData);
	}
	virtual void tick() override {

	}
};

class TWSTickByTickQuoteProvider:public ITickByTickQuoteProvider {
public:
	virtual inline void subscribeTickByTick(QuoteBaseDataPtr quoteData) override {
		Detailed::TWSQuoteProvider::getInstance()->subscribeTickByTick(quoteData);
	}
	virtual inline void cancelSubscribeTickByTick(QuoteBaseDataPtr quoteData) override {
		Detailed::TWSQuoteProvider::getInstance()->cancelSubscribeTickByTick(quoteData);
	}
	virtual void tick() override {

	}
};