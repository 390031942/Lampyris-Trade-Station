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
 * 行情接口-逐笔成交数据：
*/
class ITickByTickQuoteProvider :public IQuoteProvider {
protected:
	typedef std::unordered_map<QString, Delegate<>> TickByTickCallbackMap;
public:
	virtual void          subscibeTickByTick(const QString& code, const QString& currency = "USD") = 0;
	virtual void          cancaelSubscibeTickByTick(const QString& code, const QString& currency = "USD") = 0;
					      
	inline bool           hasSubscribeTickByTick(const QString& code) const 
	{ return this->m_tickBytickSubscribeCallbackMap.contains(code); }

	inline Delegate<>&    getTickByTickCallbackDelegate(const QString& code) {
		return this->m_tickBytickSubscribeCallbackMap[code];
	}
protected:
	TickByTickCallbackMap m_tickBytickSubscribeCallbackMap;
};