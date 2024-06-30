/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>
#include <Base/Singleton.h>
#include <Model/Quote/QuoteDataDef.h>

class MainUIStatusBarIndexBriefSubscription:public SerializableSingleton<MainUIStatusBarIndexBriefSubscription>{
	LAMPYRIS_DECLARE_SERILIZATION(MainUIStatusBarIndexBriefSubscription);
private:
	std::vector<std::string> m_subscriptionList;

	virtual void postDeserialize() override {
		if (!m_subscriptionList.size()) {
			m_subscriptionList = std::vector<std::string>({"IXIC","DJIA","SPX","HSI"});
		}
	}
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(MainUIStatusBarIndexBriefSubscription) {
	LAMPYRIS_SERIALIZATION_FIELD(m_subscriptionList);
}
LAMPYRIS_SERIALIZATION_IMPL_END;