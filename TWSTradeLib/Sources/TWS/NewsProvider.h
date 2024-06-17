/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_NEWSPROVIDER_H
#define TWS_API_CLIENT_NEWSPROVIDER_H

#include <string>
#include <Base/TWSObject.h>

struct NewsProvider:public TWSObject
{
	std::string providerCode;
	std::string providerName;

	virtual QString ToString() const override {
		return QString("{providerCode = %1, providerName = %2 }")
			.arg(providerCode.c_str()).arg(providerName.c_str());
	}
};

#endif // newsprovider_def
