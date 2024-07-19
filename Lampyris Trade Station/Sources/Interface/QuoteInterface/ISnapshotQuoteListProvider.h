/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include "IQuoteProvider.h"
#include <Model/Quote/QuoteDataDef.h>

/*
 * 行情接口-全体美股快照行情列表获取：
*/
class ISnapshotQuoteListProvider:public IQuoteProvider {
public:
	inline const std::vector<SnapshotQuoteData>& getAllSnapshotQuoteList() const { return m_allSnapshotQuoteList; }

	Delegate<const std::vector<SnapshotQuoteData>&> updateSnapshotQuoteList;
protected:
	std::vector<SnapshotQuoteData> m_allSnapshotQuoteList;
};