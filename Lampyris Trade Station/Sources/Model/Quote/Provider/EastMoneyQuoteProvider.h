/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Interface/QuoteInterface/IIndexBriefQuoteProvider.h>
#include <Network/HttpRequestManager.h>

// QT Include(s)
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class EastMoneyQuoteProvider:public IIndexBriefQuoteProvider {
	typedef std::unordered_map<QString, IndexBriefQuoteData> IndexBriefQuoteDataMap;

	enum ReqType {
		IndexBriefQuote = 1,
	};
public:
	ROIndexBriefQuoteData  queryIndexBriefQuote(const QString& code) override;
	                       EastMoneyQuoteProvider();
						  ~EastMoneyQuoteProvider();
						  
	void                   tick();
private:				  
	HttpRequestManager     m_httpRequestMgr;
	IndexBriefQuoteDataMap m_indexBriefQuoteDataMap;
};