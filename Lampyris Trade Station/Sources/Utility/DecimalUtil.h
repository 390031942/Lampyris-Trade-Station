/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Intel Decimal Floating Point Library Include(s)
#include <bid/bid_conf.h>
#include <bid/bid_functions.h>

class DecimalUtil {
public:
	static float toSingle(BID_UINT64 decimal) {
		float result = 0.0f;
		__bid64_to_binary32(result, BID_ROUNDING_TO_NEAREST, nullptr);
		return result;
	}

	static double toDouble(BID_UINT64 decimal) {
		double result  = 0.0f;
		__bid64_to_binary64(result, BID_ROUNDING_TO_NEAREST, nullptr);
		return result;
	}
};