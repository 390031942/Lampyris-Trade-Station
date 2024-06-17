/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_DEPTHMKTDATADESCRIPTION_H
#define TWS_API_CLIENT_DEPTHMKTDATADESCRIPTION_H

#include <limits.h>
#include <string>
#include <Base/TWSObject.h>

#define UNSET_INTEGER INT_MAX

struct DepthMktDataDescription:public TWSObject
{
	DepthMktDataDescription()
		: exchange("")
		, secType("")
		, listingExch("")
		, serviceDataType("")
		, aggGroup(UNSET_INTEGER)
	{
	}

	std::string exchange;
	std::string secType;
	std::string listingExch;
	std::string serviceDataType;
	int aggGroup;

	virtual QString ToString() const override {
		return QString("{exchange: %1, secType: %2, listingExch = %3, serviceDataType = %4, aggGroup = %5}")
			.arg(exchange.c_str()).arg(secType.c_str())
			.arg(listingExch.c_str()).arg(serviceDataType.c_str()).arg(aggGroup);
	}
};

#endif // depthmktdatadescription_def
