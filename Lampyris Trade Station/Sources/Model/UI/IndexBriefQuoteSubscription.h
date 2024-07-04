/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>
#include <Base/Singleton.h>
#include <Model/Quote/QuoteDataDef.h>

class IndexBriefQuoteSubscription
	:public SerializableSingleton<IndexBriefQuoteSubscription>{
	LAMPYRIS_DECLARE_SERILIZATION(IndexBriefQuoteSubscription);
public:
	inline std::vector<QString>& getSubscribedList()
	{ return m_subscriptionList; }

private:
	std::vector<QString> m_subscriptionList;

	virtual void postDeserialize() override {
		if (!m_subscriptionList.size()) {
			m_subscriptionList = std::vector<QString>({"NDX","DJIA","SPX"});
		}
	}
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(IndexBriefQuoteSubscription) {
	LAMPYRIS_SERIALIZATION_FIELD(m_subscriptionList);
}
LAMPYRIS_SERIALIZATION_IMPL_END;