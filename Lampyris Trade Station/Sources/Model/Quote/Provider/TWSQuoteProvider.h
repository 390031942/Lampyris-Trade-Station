/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Base/EventDispatcher.h>

// STD Include(s)
#include <vector>
#include <unordered_set>
#include <unordered_map>

class TWSQuoteProvider {
public:
	TWSQuoteProvider();
	
	~TWSQuoteProvider();

	void subscribeScanner(const ScannerSubscription subscription, 
		                  const TagValueListSPtr& scannerSubscriptionOptions = TagValueListSPtr(),
		                  const TagValueListSPtr& scannerSubscriptionFilterOptions = TagValueListSPtr());

	void subscribeStock(const std::string& name);

	void cancelSubscribeStock(const std::string& name);

	void subscribeStockList(const std::vector<std::string> list);

	void cancelSubscribeStockList(const std::vector<std::string> list);
private:
	void bindEvent();

	std::function<void(int reqId,
		               int rank,
		               const ContractDetails& contractDetails,
		               const std::string& distance,
		               const std::string& benchmark,
		               const std::string& projection,
		               const std::string& legsStr)> m_onResScannerData;

	std::function<void(int reqId)> m_onResScannerDataEnd;

	void handleResScannerData(int reqId,
		                      int rank,
		                      const ContractDetails& contractDetails,
		                      const std::string& distance,
		                      const std::string& benchmark,
		                      const std::string& projection,
		                      const std::string& legsStr);

	void handleResScannerDataEnd(int reqId);


	/************** tickerId 变量 begin **************/
	int m_tickerIdAutoIncrement = 0;
	int m_scannerTickerId = -1;
	/************** tickerId 变量 end **************/

	std::unordered_map<std::string,int> m_subscribeStockCode2TickerId;
};