/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_FAMILYCODE_H
#define TWS_API_CLIENT_FAMILYCODE_H

#include <string>
#include <Base/TWSObject.h>

struct FamilyCode:public TWSObject
{
	std::string accountID;
	std::string familyCodeStr;

	virtual QString ToString() const override {
		return QString("{accountID: %1, familyCodeStr: %2}")
			.arg(accountID.c_str()).arg(familyCodeStr.c_str());
	}
};

#endif // familycode_def
