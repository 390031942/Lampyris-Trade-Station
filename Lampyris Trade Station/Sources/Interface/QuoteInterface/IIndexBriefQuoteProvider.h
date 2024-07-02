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
 * ����ӿ�-ָ����Ҫ���飺
*/
class IIndexBriefQuoteProvider:public IQuoteProvider {
protected:
	typedef const IndexBriefQuoteData& ROIndexBriefQuoteData;
public:
	/* 
	 * ������Ҫ���ĵ�ָ����Ҫ��������б�
	 * ����{codeList}:ָ�������б�
	*/
	inline void setSubscribeList(const std::vector<QString>& codeList)
	{ this->m_codeList = codeList; }

	/* 
	 * ���ݴ����ѯָ����Ҫ����
	 * ����{code}:ָ������
	 * ����: IndexBriefQuoteData������
	*/
	virtual ROIndexBriefQuoteData queryIndexBriefQuote(const QString& code) const = 0;
protected:
	/* 
	 * ָ�������б�
	*/
	std::vector<QString> m_codeList;
};