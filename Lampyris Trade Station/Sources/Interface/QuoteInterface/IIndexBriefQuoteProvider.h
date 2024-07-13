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
 * 行情接口-指数简要行情：
*/
class IIndexBriefQuoteProvider: public IQuoteProvider {
protected:
	typedef const IndexBriefQuoteData& ROIndexBriefQuoteData;
public:
	/* 
	 * 设置需要订阅的指数简要行情代码列表
	 * 参数{codeList}:指数代码列表
	*/
	inline void setSubscribeList(const std::vector<QString>& codeList)
	{ this->m_codeList = codeList; }

	/* 
	 * 根据代码查询指数简要行情
	 * 参数{code}:指数代码
	 * 返回: IndexBriefQuoteData常引用
	*/
	virtual const IndexBriefQuoteData& queryIndexBriefQuote(const QString& code) = 0;
protected:
	/* 
	 * 指数代码列表
	*/
	std::vector<QString> m_codeList;
};