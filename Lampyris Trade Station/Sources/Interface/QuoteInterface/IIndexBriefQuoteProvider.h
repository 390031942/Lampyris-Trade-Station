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
public:
	virtual const IndexBriefQuoteData& query(const QString& code) = 0;
};