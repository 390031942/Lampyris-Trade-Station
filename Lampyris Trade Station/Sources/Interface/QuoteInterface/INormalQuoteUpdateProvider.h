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
 * ����ӿ�-��ͨ������µĽӿڣ�ͨ������ "�Ǻ��뼶" ���������ݸ��£�
*/
class INormalQuoteUpdateProvider :public IQuoteProvider {
protected:
	typedef std::unordered_map<QString, QuoteBaseDataPtr> QuoteDataMap;
public:
	virtual void subscribeQuoteUpdate(QuoteBaseDataPtr quoteData) = 0;						
	virtual void cancelSubscribeQuoteUpdate(QuoteBaseDataPtr quoteData) = 0;
protected:			 
	QuoteDataMap m_quoteDataMap;
};