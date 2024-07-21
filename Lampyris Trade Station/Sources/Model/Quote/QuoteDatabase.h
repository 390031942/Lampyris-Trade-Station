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
#include <Interface/QuoteInterface/ISnapshotQuoteListProvider.h>

// TWS Include(s)
#include <TWS/ScannerSubscription.h>

class QuoteDatabase:public SerializableSingleton<QuoteDatabase> {
	typedef Delegate<> UpdateIndexBriefQuoteCallback;
	typedef std::unordered_map<QString, QuoteBaseDataPtr> QuoteDataMap;
	typedef std::vector<QuoteBaseDataPtr> SearchResultList;

	LAMPYRIS_DECLARE_SERILIZATION(QuoteDatabase);
public:
	enum BuildInScannerType {
		PreMarketTopGainer = 0,
		InMarketTopGainer = 1,
		AfterHourTopGainer = 2,
		Count = 3,
	};

	QuoteDataReader               query(const QString& code, const QString& currency = "USD");
	SearchResultList              search(const QString& input);
	void                          searchNoAlloc(const QString& input, SearchResultList& list);

	// For 股票列表
	void                          refreshStockList();
	void                          setSnapShotQuoteListProvider(ISnapshotQuoteListProvider* provider);

	// For 指数简要行情 IndexBriefQuote
	const IndexBriefQuoteData&    queryIndexBriefQuote(const QString& code);
	void                          subscribeIndexBriefQuote(const std::vector<QString>& codeList);
	void                          setIndexBriefQuoteProvider(IIndexBriefQuoteProvider* provider);
	UpdateIndexBriefQuoteCallback onUpdatendexBriefQuote;

	// For 逐笔行情Tick-by-Tick

	// For 查询TWS扫描器返回结果的合约列表(这里不用提供抽象的接口类了，因为一定要用TWS的)
	int                           commitScannerSubscription(const ScannerSubscription& scannerSubscription);
	void                          cancelScannerSubscription(int scannerId);
	std::vector<Contract>         getScannerResult(int scannerId);
	int                           m_scannerIdIncrement = BuildInScannerType::Count;

	QuoteDatabase();
private:
	void                          tick();
	std::vector<QString>          m_subscribeIndexBriefQuoteCodeList;
	//  currency -> [code -> SecurityDataPtr]
	QuoteDataMap                  m_dataMap;

	IIndexBriefQuoteProvider*     m_indexBriefQuoteProvider;
	ITickByTickQuoteProvider*     m_tickByTickQuoteProvider;
	ISnapshotQuoteListProvider*   m_snapshotQuoteListProvider;

	// callback id(s)
	int                           m_updateSnapShotQuoteListCallbackId;

	int                           m_indexBriefQuoteTickIntervalMs = 3000;
	std::unordered_map<int, std::vector<Contract>> m_scannerReqId2DataListMap;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteDatabase) 
{
	// LAMPYRIS_SERIALIZATION_FIELD(m_dataList);
	LAMPYRIS_SERIALIZATION_FIELD(m_indexBriefQuoteTickIntervalMs);
}
LAMPYRIS_SERIALIZATION_IMPL_END;