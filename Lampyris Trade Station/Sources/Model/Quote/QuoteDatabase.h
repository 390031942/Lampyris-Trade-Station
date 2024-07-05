/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>
#include <QTimer>

// TWS API Include(s)
#include <TWS/Contract.h>

// STD Include(s)
#include <fstream>
#include <vector>
#include <unordered_map>

// Project Include(s)
#include "QuoteDataDef.h"
#include <Base/SerializeMacro.h>
#include <Base/Delegate.h>
#include <Base/SerializableSingleton.h>
#include <Interface/QuoteInterface/IIndexBriefQuoteProvider.h>
#include <Interface/QuoteInterface/ITickByTickQuoteProvider.h>

// TWS Include(s)
#include <TWS/ScannerSubscription.h>

class QuoteDatabase:public SerializableSingleton<QuoteDatabase> {
	typedef Delegate<> UpdateIndexBriefQuoteCallback;
	typedef std::unordered_map<QString, std::unordered_map<QString, QuoteBaseDataPtr>> QuoteDataMap;
	typedef std::vector<std::pair<QString, std::pair<QString, QuoteBaseDataPtr>>> QuoteDataList;

	LAMPYRIS_DECLARE_SERILIZATION(QuoteDatabase);
public:
	void                          query(const QString& code, const QString& currency = "USD");

	// For 指数简要行情 IndexBriefQuote
	const IndexBriefQuoteData&    queryIndexBriefQuote(const QString& code);
	void                          subscribeIndexBriefQuote(const std::vector<QString>& codeList);
	void                          setIndexBriefQuoteProvider(IIndexBriefQuoteProvider* provider);
	UpdateIndexBriefQuoteCallback onUpdatendexBriefQuote;

	// For 逐笔行情Tick-by-Tick

	// For 查询TWS扫描器返回结果的合约列表(这里不用提供抽象的接口类了，因为一定要用TWS的)
	void                          commitScannerSubscription(const ScannerSubscription& scannerSubscription);
	void                          cancelScannerSubscription();

	QuoteDatabase();
private:
	void                          tick();
	std::vector<QString>          m_subscribeIndexBriefQuoteCodeList;
	//  currency -> [code -> SecurityDataPtr]
	QuoteDataMap                  m_dataMap;
	QuoteDataList                 m_dataList;

	IIndexBriefQuoteProvider*     m_indexBriefQuoteProvider;
	ITickByTickQuoteProvider*     m_tickByTickQuoteProvider;

	int                           m_indexBriefQuoteTickIntervalMs = 3000;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteDatabase) 
{
	// LAMPYRIS_SERIALIZATION_FIELD(m_dataList);
	LAMPYRIS_SERIALIZATION_FIELD(m_indexBriefQuoteTickIntervalMs);
}
LAMPYRIS_SERIALIZATION_IMPL_END;