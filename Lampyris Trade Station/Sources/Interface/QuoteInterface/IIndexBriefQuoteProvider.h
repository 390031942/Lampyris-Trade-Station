/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Model/Quote/QuoteDataDef.h>

/*
 * 行情接口-指数简要行情：
*/
class IIndexBriefQuoteProvider {
protected:
	typedef const IndexBriefQuoteData& ROIndexBriefQuoteData;
public:
	virtual ROIndexBriefQuoteData queryIndexBriefQuote(const QString& code) const = 0;
};