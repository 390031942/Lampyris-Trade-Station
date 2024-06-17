/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_TICKATTRIB_H
#define TWS_API_CLIENT_TICKATTRIB_H

#include <Base/TWSObject.h>

struct TickAttrib:public TWSObject
{
	bool canAutoExecute;
	bool pastLimit;
	bool preOpen;

	virtual QString ToString() const override {
		return QString("{canAutoExecute = %1, pastLimit = %2, preOpen = %3}")
			.arg(canAutoExecute).arg(pastLimit).arg(preOpen);
	}
};

#endif
