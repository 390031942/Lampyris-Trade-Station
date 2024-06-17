/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_HISTOGRAMENTRY_H
#define TWS_API_CLIENT_HISTOGRAMENTRY_H

#include "Decimal.h"
#include <Base/TWSObject.h>

struct HistogramEntry :public TWSObject
{
	double price;
	Decimal size;

    virtual QString ToString() const override {
        return QString("{price = %1, size = %2}")
            .arg(price).arg(size);
    }
};

#endif
