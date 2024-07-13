/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Core/TWSEventDispatcher.h>
#include <Interface/QuoteInterface/ITickByTickQuoteProvider.h>

// STD Include(s)
#include <vector>
#include <unordered_set>
#include <unordered_map>

class TWSQuoteProvider:public ITickByTickQuoteProvider {
public:
	void          subscribeScanner(const ScannerSubscription subscription, 
		                           const TagValueListSPtr& scannerSubscriptionOptions = TagValueListSPtr(),
		                           const TagValueListSPtr& scannerSubscriptionFilterOptions = TagValueListSPtr());

	void          subscribeMarketData(const std::string& name, const std::string& currency = "USD");
	void          subscribeMarketData(const std::vector<std::string> list, const std::string& currency = "USD");

	void          cancelSubscribeMarketData(const std::string& name);
	void          cancelSubscribeMarketData(const std::vector<std::string> list);
  
	              TWSQuoteProvider();
	             ~TWSQuoteProvider();
private:
	void bindEvent();
	
	int m_tickerIdAutoIncrement = 0;
	int m_scannerTickerId = -1;
	int m_scannerReqId = -1;

	std::unordered_map<std::string,int> m_subscribeStockCode2TickerId;
	std::vector<ContractDetails> m_scannerResult;
};