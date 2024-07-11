/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>
#include <Const/StrategyResult.h>

struct StrategyStateObject {
	LAMPYRIS_DECLARE_SERILIZATION(StrategyStateObject);
	bool                 active;
	long                 lastTriggeredTimeStmap;
	long                 lastExecutionResultTimeStmap;
	StrategyResult       lastResult;
	std::vector<QString> executionlog;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(StrategyStateObject)
{
	LAMPYRIS_SERIALIZATION_FIELD(active);
	LAMPYRIS_SERIALIZATION_FIELD(lastTriggeredTimeStmap);
	LAMPYRIS_SERIALIZATION_FIELD(lastExecutionResultTimeStmap);
	LAMPYRIS_SERIALIZATION_FIELD(lastResult);
	LAMPYRIS_SERIALIZATION_FIELD(executionlog);
}
LAMPYRIS_SERIALIZATION_IMPL_END

class IStrategy;

class StrategyDataBase:public SerializableSingleton<StrategyDataBase> {
	LAMPYRIS_DECLARE_SERILIZATION(StrategyDataBase);
public:
	StrategyStateObject* getStateObject(const QString& strategyName);

	void registerStrategy(IStrategy* strategy);
private:
	std::unordered_map<QString, StrategyStateObject> m_name2StateObjectMap;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(StrategyDataBase)
{
	LAMPYRIS_SERIALIZATION_FIELD(m_name2StateObjectMap);
}
LAMPYRIS_SERIALIZATION_IMPL_END