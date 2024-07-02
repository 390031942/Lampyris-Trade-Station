/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/Delegate.h>

/*
 * 行情接口基类：
*/
class IQuoteProvider {
public:
	/* 
	 * QuoteProvider被tick并更新行情时调用的函数
	*/
	Delegate<> updateQuoteCallback;
protected:
	/* 
	 * QuoteProvider被tick的时间戳，常用于间隔控制 和 行情实时性检验
	*/
	long m_lastTickTimestmap;

	/* 
	 * 当QuoteProvider被tick后数据准备完毕会设置为true，使用完毕后重新设置为false
	*/
	bool m_isReady = false;

	/* 
	 * tick函数用于请求行情更新
	*/
	virtual void tick() = 0;

	friend class QuoteDatabase;
};