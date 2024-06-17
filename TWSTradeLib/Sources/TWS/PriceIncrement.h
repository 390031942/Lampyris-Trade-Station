/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_PRICEINCREMENT_H
#define TWS_API_CLIENT_PRICEINCREMENT_H

#include <Base/TWSObject.h>

struct PriceIncrement:public TWSObject
{
	double lowEdge;
	double increment;

	virtual QString ToString() const override {
		return QString("{lowEdge = %1, increment = %2}")
			.arg(lowEdge).arg(increment);
	}
};

#endif // priceincrement_def
