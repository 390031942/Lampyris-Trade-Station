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
 * ����ӿ�-ȫ�����ɴ����б��ȡ��
*/
class IStockCodeListProvider:public IQuoteProvider {
public:
	inline const std::vector<QString>& getAllStockCodeList() const { return m_allStockCodeList; }
protected:
	std::vector<QString> m_allStockCodeList;
};