/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/Delegate.h>

/*
 * ����ӿ�-ָ����Ҫ���飺
*/
class IQuoteProvider {
public:
	Delegate<> updateQuoteCallback;
};