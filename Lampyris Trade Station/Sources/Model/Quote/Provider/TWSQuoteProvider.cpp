/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "TWSQuoteProvider.h"

// TWS Include(s)
#include <TWS/ScannerSubscription.h>

TWSQuoteProvider::TWSQuoteProvider() {
}

TWSQuoteProvider::~TWSQuoteProvider() {

}

void TWSQuoteProvider::subscribeScanner(const ScannerSubscription subscription, 
	                                    const TagValueListSPtr& scannerSubscriptionOptions, 
	                                    const TagValueListSPtr& scannerSubscriptionFilterOptions) {
	TWS->reqScannerSubscription(m_scannerTickerId = m_tickerIdAutoIncrement++, subscription, scannerSubscriptionOptions, scannerSubscriptionFilterOptions);
}

void TWSQuoteProvider::subscribeMarketData(const std::string& name, const std::string& currency) {
	if (m_subscribeStockCode2TickerId.contains(name)) {
		return;
	}

	int tickerId = m_tickerIdAutoIncrement++;

	Contract contract;
	contract.symbol = name;
	contract.secType = "STK";
	contract.currency = currency;
	contract.exchange = "SMART";

	TWS->reqMktData(tickerId, contract, "LAST", false, false, TagValueListSPtr());
	m_subscribeStockCode2TickerId[name] = tickerId;
}

void TWSQuoteProvider::cancelSubscribeMarketData(const std::string& name) {
	if (!m_subscribeStockCode2TickerId.contains(name)) {
		return;
	}

	int tickerId = m_subscribeStockCode2TickerId[name];
	TWS->cancelMktData(tickerId);
}

void TWSQuoteProvider::subscribeMarketData(const std::vector<std::string> list, const std::string& currency) {
	for (const std::string& stockCode : list) {
		subscribeMarketData(stockCode,currency);
	}
}

void TWSQuoteProvider::cancelSubscribeMarketData(const std::vector<std::string> list) {
	for (const std::string& stockCode : list) {
		cancelSubscribeMarketData(stockCode);
	}
}

void TWSQuoteProvider::bindEvent() {
	TWSEventBind(TWSEventType::onResTickPrice, [=](TickerId tickerId, TickType field, double price, const TickAttrib& attrib) {
		
	});

	TWSEventBind(TWSEventType::onResTickSize, [=](TickerId tickerId, TickType field, Decimal size) {
		
	});

	TWSEventBind(TWSEventType::onResTickString, [=](TickerId tickerId, TickType tickType, const std::string& value) {

	});

	TWSEventBind(TWSEventType::onResTickGeneric, [=](TickerId tickerId, TickType tickType, double value) {

	});
}