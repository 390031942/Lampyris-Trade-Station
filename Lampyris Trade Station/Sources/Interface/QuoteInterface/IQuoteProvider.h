/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/Delegate.h>

/*
 * 行情接口-指数简要行情：
*/
class IQuoteProvider {
public:
	Delegate<> updateQuoteCallback;
};