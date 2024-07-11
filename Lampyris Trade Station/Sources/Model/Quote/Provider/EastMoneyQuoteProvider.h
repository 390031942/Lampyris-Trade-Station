/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Interface/QuoteInterface/IIndexBriefQuoteProvider.h>
#include <Interface/QuoteInterface/IStockCodeListProvider.h>
#include <Network/HttpRequestManager.h>

// QT Include(s)
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class EastMoneyQuoteProvider:public IIndexBriefQuoteProvider, public IStockCodeListProvider {
	typedef std::unordered_map<QString, IndexBriefQuoteData> IndexBriefQuoteDataMap;

	enum ReqType {
		IndexBriefQuote = 1,
		AllStockCodeList = 2,
	};
public:
	ROIndexBriefQuoteData  queryIndexBriefQuote(const QString& code) override;
	                       EastMoneyQuoteProvider();
						  ~EastMoneyQuoteProvider();
private:				  
	HttpRequestManager     m_httpRequestMgr;
	IndexBriefQuoteDataMap m_indexBriefQuoteDataMap;

	inline void            IIndexBriefQuoteProvider::IQuoteProvider::tick()
	{ this->onTickIndexBriefQuoteProvider();}

	// inline void            IStockCodeListProvider::IQuoteProvider::tick()
	// { this->onTickStockCodeListProvider(); }

	void                   onTickIndexBriefQuoteProvider();
	void                   onTickStockCodeListProvider();
};