/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QObject>

// Project Include(s)
#include <Model/Strategy/StrategyDescription.h>
#include <Const/StrategyState.h>
#include <Base/ClassInitializer.h>

/*
 * 程序化执行策略的接口类：
*/
class IStrategy:public QObject {
public:
	inline const StrategyDescription& getDescription() const 
	{ return this->m_description; }

	virtual StrategyState getState() {
		return StrategyState::NotActive;
	}
protected:
	StrategyDescription m_description;
};

#ifndef LAMPYRIS_STRATEGY_MACRO
 #define LAMPYRIS_STRATEGY_DECLARE(clsName) \
     Q_OBJECT;  \
     LAMPYRIS_DECLARE_CLASS_INITIALIZE(clsName);

#define LAMPYRIS_STRATEGY_IMPL(clsName,name,author,desc) \
	LAMPYRIS_DECLARE_CLASS_BEGIN(clsName) {\
	this->m_description.name = name;this->m_description.desc = desc;this->m_description.author = author;\
    StrategyDataBase::getInstance()->registerStrategy(this);\
	}\
	LAMPYRIS_DECLARE_CLASS_END

#endif // !LAMPYRIS_STRATEGY_MACRO