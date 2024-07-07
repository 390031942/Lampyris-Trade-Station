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
	void          subscribeStock(const std::string& name);
	void          cancelSubscribeStock(const std::string& name);
	void          subscribeStockList(const std::vector<std::string> list);
	void          cancelSubscribeStockList(const std::vector<std::string> list);
  
	              TWSQuoteProvider();
	             ~TWSQuoteProvider();
private:
	/************** ˽�� ���� begin **************/
	void bindEvent();
	/************** ˽�з��� end **************/
	
	/************** tickerId ���� begin **************/
	int m_tickerIdAutoIncrement = 0;
	int m_scannerTickerId = -1;
	int m_scannerReqId = -1;
	/************** tickerId ���� end **************/

	std::unordered_map<std::string,int> m_subscribeStockCode2TickerId;
	std::vector<ContractDetails> m_scannerResult;
};