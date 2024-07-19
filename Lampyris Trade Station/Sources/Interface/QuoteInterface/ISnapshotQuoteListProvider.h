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
 * ����ӿ�-ȫ�����ɿ��������б��ȡ��
*/
class ISnapshotQuoteListProvider:public IQuoteProvider {
public:
	inline const std::vector<SnapshotQuoteData>& getAllSnapshotQuoteList() const { return m_allSnapshotQuoteList; }

	Delegate<const std::vector<SnapshotQuoteData>&> updateSnapshotQuoteList;
protected:
	std::vector<SnapshotQuoteData> m_allSnapshotQuoteList;
};