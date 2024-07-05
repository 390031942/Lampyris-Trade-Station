/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Base/EventDispatcher.h>
#include <Interface/QuoteInterface/ITickByTickQuoteProvider.h>

// STD Include(s)
#include <vector>
#include <unordered_set>
#include <unordered_map>

class TWSQuoteProvider:public ITickByTickQuoteProvider {
public:
	void subscribeScanner(const ScannerSubscription subscription, 
		                  const TagValueListSPtr& scannerSubscriptionOptions = TagValueListSPtr(),
		                  const TagValueListSPtr& scannerSubscriptionFilterOptions = TagValueListSPtr());
	void subscribeStock(const std::string& name);
	void cancelSubscribeStock(const std::string& name);
	void subscribeStockList(const std::vector<std::string> list);
	void cancelSubscribeStockList(const std::vector<std::string> list);
  
	     TWSQuoteProvider();
	    ~TWSQuoteProvider();
private:
	/************** ˽�з��� begin **************/
	void bindEvent();
	/************** ˽�з��� end **************/

	/************** EWrapper�¼��Ĵ���Lambda��װ���� begin **************/
	std::function<void(int reqId,
		               int rank,
		               const ContractDetails& contractDetails,
		               const std::string& distance,
		               const std::string& benchmark,
		               const std::string& projection,
		               const std::string& legsStr)> m_onResScannerData;

	std::function<void(int reqId)> m_onResScannerDataEnd;
	/************** EWrapper�¼��Ĵ���Lambda��װ����  end **************/


	/************** EWrapper�¼��Ĵ����� begin **************/
	void handleResScannerData(int reqId,
		                      int rank,
		                      const ContractDetails& contractDetails,
		                      const std::string& distance,
		                      const std::string& benchmark,
		                      const std::string& projection,
		                      const std::string& legsStr);

	void handleResScannerDataEnd(int reqId);
	/************** EWrapper�¼��Ĵ����� begin **************/

	
	/************** tickerId ���� begin **************/
	int m_tickerIdAutoIncrement = 0;
	int m_scannerTickerId = -1;
	int m_scannerReqId = -1;
	/************** tickerId ���� end **************/

	std::unordered_map<std::string,int> m_subscribeStockCode2TickerId;
	std::vector<ContractDetails> m_scannerResult;
};