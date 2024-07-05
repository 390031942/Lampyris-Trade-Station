/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "TWSQuoteProvider.h"

// TWS Include(s)
#include <TWS/ScannerSubscription.h>

TWSQuoteProvider::TWSQuoteProvider() {
	this->m_onResScannerData = [=](int reqId, 
		                           int rank, 
		                           const ContractDetails& contractDetails, 
		                           const std::string& distance, 
		                           const std::string& benchmark,
		                           const std::string& projection,
		                           const std::string& legsStr) {
		this->handleResScannerData(reqId,rank, contractDetails, distance, benchmark, projection, legsStr);
	};

	this->m_onResScannerDataEnd = [=](int reqId) {
		this->handleResScannerDataEnd(reqId);
	};
}

TWSQuoteProvider::~TWSQuoteProvider() {

}

void TWSQuoteProvider::subscribeScanner(const ScannerSubscription subscription, 
	                                    const TagValueListSPtr& scannerSubscriptionOptions, 
	                                    const TagValueListSPtr& scannerSubscriptionFilterOptions) {
	TWS->reqScannerSubscription(m_scannerTickerId = m_tickerIdAutoIncrement++, subscription, scannerSubscriptionOptions, scannerSubscriptionFilterOptions);
}

void TWSQuoteProvider::subscribeStock(const std::string& name) {
	if (m_subscribeStockCode2TickerId.contains(name)) {
		return;
	}

	int tickerId = m_tickerIdAutoIncrement++;

	Contract contract;
	contract.symbol = name;
	contract.secType = "STK";
	contract.currency = "USD";
	contract.exchange = "SMART";

	TWS->reqMktData(tickerId, contract, "LAST", false, false, TagValueListSPtr());
	m_subscribeStockCode2TickerId[name] = tickerId;
}

void TWSQuoteProvider::cancelSubscribeStock(const std::string& name) {
	if (!m_subscribeStockCode2TickerId.contains(name)) {
		return;
	}

	int tickerId = m_subscribeStockCode2TickerId[name];
	TWS->cancelMktData(tickerId);
}

void TWSQuoteProvider::subscribeStockList(const std::vector<std::string> list) {
	for (const std::string& stockCode : list) {
		subscribeStock(stockCode);
	}
}

void TWSQuoteProvider::cancelSubscribeStockList(const std::vector<std::string> list) {
	for (const std::string& stockCode : list) {
		cancelSubscribeStock(stockCode);
	}
}

void TWSQuoteProvider::bindEvent() {
	EventBind(EventType::onResScannerData, this->m_onResScannerData);
	EventBind(EventType::onResScannerDataEnd, this->m_onResScannerDataEnd);
}

void TWSQuoteProvider::handleResScannerData(int reqId, 
	                                        int rank, 
	                                        const ContractDetails& contractDetails, 
	                                        const std::string& distance, 
	                                        const std::string& benchmark,
	                                        const std::string& projection, 
	                                        const std::string& legsStr) {
	if (this->m_scannerReqId < 0) {
		m_scannerResult.clear();
	}

	m_scannerResult.push_back(contractDetails);
}

void TWSQuoteProvider::handleResScannerDataEnd(int reqId) {
	this->m_scannerReqId = 0;
}
