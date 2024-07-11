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
#include <Model/Strategy/StrategyDatabase.h>

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
	
	virtual bool executeCondition() = 0;

	virtual bool tick() = 0;
protected:
	StrategyDescription m_description;
};

#ifndef LAMPYRIS_STRATEGY_MACRO
 #define LAMPYRIS_STRATEGY_DECLARE(clsName) \
     Q_OBJECT;  \
     LAMPYRIS_DECLARE_CLASS_INITIALIZE(clsName);

 #define LAMPYRIS_STRATEGY_IMPL(clsName,_name,_author,_desc) \
 	 LAMPYRIS_DECLARE_CLASS_BEGIN(clsName) {\
 		auto _this = new clsName();\
 		_this->m_description.name = _name;_this->m_description.desc = _desc;_this->m_description.author = _author;\
		StrategyDataBase::getInstance()->registerStrategy(_this);\
 	 }\
	LAMPYRIS_DECLARE_CLASS_END

#endif // !LAMPYRIS_STRATEGY_MACRO