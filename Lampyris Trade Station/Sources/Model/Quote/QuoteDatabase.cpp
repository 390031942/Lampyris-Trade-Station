/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QuoteDatabase.h"
#include <Core/Application.h>

void QuoteDatabase::query(const QString& code, const QString& currency) {

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

QuoteDatabase::QuoteDatabase() {
	Application::addTickFunc([=]() {
		this->tick();
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
