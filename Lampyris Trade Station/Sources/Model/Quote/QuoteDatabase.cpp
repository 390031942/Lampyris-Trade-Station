/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QuoteDatabase.h"
#include <Core/Application.h>
#include <Core/TWSEventDispatcher.h>

QuoteBaseDataPtr QuoteDatabase::query(const QString& code, const QString& currency) {

}

const IndexBriefQuoteData& QuoteDatabase::queryIndexBriefQuote(const QString& code) {
	return this->m_indexBriefQuoteProvider->queryIndexBriefQuote(code);
}

void QuoteDatabase::subscribeIndexBriefQuote(const std::vector<QString>& codeList) {
	m_subscribeIndexBriefQuoteCodeList = codeList;
}

void QuoteDatabase::setIndexBriefQuoteProvider(IIndexBriefQuoteProvider* provider) {
	this->m_indexBriefQuoteProvider = provider;
}

int QuoteDatabase::commitScannerSubscription(const ScannerSubscription& scannerSubscription) {
	int tickerId = this->m_scannerIdIncrement++;
	TWS->reqScannerSubscription(tickerId,scannerSubscription,TagValueListSPtr(), TagValueListSPtr());

	return tickerId;
}

void QuoteDatabase::cancelScannerSubscription(int scannerId) {
	TWS->cancelScannerSubscription(scannerId);
}

std::vector<Contract> QuoteDatabase::getScannerResult(int scannerId) {
	return m_scannerReqId2DataListMap[scannerId];
}

QuoteDatabase::QuoteDatabase() {
	Application::addTickFunc([=]() {
		this->tick();
	});

	TWSEventBind(TWSEventType::onResScannerDataEnd, [=](int scannerReqId,const std::vector<Contract>& result) {
		m_scannerReqId2DataListMap[scannerReqId] = result;
	});
}

void QuoteDatabase::tick() {
	long timeStmap = QDateTime::currentDateTime().toTime_t();
	if (m_indexBriefQuoteProvider->m_isReady) {
		onUpdatendexBriefQuote();
		m_indexBriefQuoteProvider->m_isReady = false;
	}
	else {
		if (timeStmap - m_indexBriefQuoteProvider->m_lastTickTimestmap > this->m_indexBriefQuoteTickIntervalMs) {
			m_indexBriefQuoteProvider->tick();
			m_indexBriefQuoteProvider->m_lastTickTimestmap = timeStmap;
		}
	}

}
