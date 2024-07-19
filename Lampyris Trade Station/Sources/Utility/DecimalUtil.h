/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Intel Decimal Floating Point Library Include(s)
#include <TWS/Decimal.h>

class DecimalUtil {
public:
	static float toSingle(Decimal decimal) {
		float result = 0.0f;
		__bid64_to_binary64(result, 0, nullptr);
		return result;
	}

	static double toDouble(Decimal decimal) {
		double result  = 0.0f;
		__bid64_to_binary64(result, 0, nullptr);
		return result;
	}
};