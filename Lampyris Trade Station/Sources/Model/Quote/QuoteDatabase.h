/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// TWS API Include(s)
#include <TWS/Contract.h>

// STD Include(s)
#include <vector>
#include <unordered_map>

// Project Include(s)
#include "QuoteDataDef.h"
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>

class QuoteDatabase:public SerializableSingleton<QuoteDatabase> {
	LAMPYRIS_DECLARE_SERILIZATION(QuoteDatabase);
public:
	void query(const QString& name, const QString& currency = "USD") {
		
	}
private:
	//  currency -> [code -> SecurityDataPtr]
	std::unordered_map<QString, std::unordered_map<QString, SecurityDataPtr>> m_dataMap;
	std::vector<std::pair<QString, std::pair<QString, SecurityDataPtr>>> m_dataList;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteDatabase) 
{
	LAMPYRIS_SERIALIZATION_FIELD(m_dataList);
}
LAMPYRIS_SERIALIZATION_IMPL_END;