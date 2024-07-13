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

namespace Detailed {
class EastMoneyQuoteProvider:public Singleton<EastMoneyQuoteProvider> {
	typedef std::unordered_map<QString, IndexBriefQuoteData> IndexBriefQuoteDataMap;

	enum ReqType {
		IndexBriefQuote = 1,
		AllStockCodeList = 2,
	};
public:
	const IndexBriefQuoteData& queryIndexBriefQuote(const QString& code);

	// ticker(s)
	void                       onTickIndexBriefQuoteProvider();
	void                       onTickStockCodeListProvider();

	                           EastMoneyQuoteProvider();
						      ~EastMoneyQuoteProvider();
private:				      
	HttpRequestManager         m_httpRequestMgr;
	IndexBriefQuoteDataMap     m_indexBriefQuoteDataMap;
						      
};						       
} // end of namespace 'Detailed'

class EastMoneyIndexBriefQuoteProvider :public IIndexBriefQuoteProvider {
public:
	virtual inline const IndexBriefQuoteData& queryIndexBriefQuote(const QString& code) override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->queryIndexBriefQuote(code);
	}

	virtual inline void tick() override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->onTickIndexBriefQuoteProvider();
	}
};

class EastMoneyIStockCodeListProvider :public IStockCodeListProvider {
public:
	virtual inline void tick() override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->onTickStockCodeListProvider();
	}
};