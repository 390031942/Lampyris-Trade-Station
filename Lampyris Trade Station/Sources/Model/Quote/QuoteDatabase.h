/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

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

class QuoteDatabase:public SerializableSingleton<QuoteDatabase> {
	typedef Delegate<const std::vector<IndexBriefQuoteData>&> UpdateIndexBriefQuoteCallback;
	typedef std::unordered_map<QString, std::unordered_map<QString, QuoteBaseDataPtr>> QuoteDataMap;
	typedef std::vector<std::pair<QString, std::pair<QString, QuoteBaseDataPtr>>> QuoteDataList;

	LAMPYRIS_DECLARE_SERILIZATION(QuoteDatabase);
public:
	void query(const QString& code, const QString& currency = "USD") {
		
	}

	void subscribeIndexBriefQuote(const std::vector<QString>& codeList) {
		m_subscribeIndexBriefQuoteCodeList = codeList;
	}

	// 外部更新行情数据的回调
	UpdateIndexBriefQuoteCallback onUpdatendexBriefQuote;
private:
	std::vector<QString> m_subscribeIndexBriefQuoteCodeList;
	//  currency -> [code -> SecurityDataPtr]
	QuoteDataMap m_dataMap;
	QuoteDataList m_dataList;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteDatabase) 
{
	LAMPYRIS_SERIALIZATION_FIELD(m_dataList);
}
LAMPYRIS_SERIALIZATION_IMPL_END;