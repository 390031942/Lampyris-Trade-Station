/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_BAR_H
#define TWS_API_CLIENT_BAR_H

#include <string>
#include "Decimal.h"

#include <Base/TWSObject.h>

struct Bar:public TWSObject 
{
	std::string time;
	double high;
	double low;
	double open;
	double close;
	Decimal wap;
	Decimal volume;
	int count;

    virtual QString ToString() const override {
        return QString("{time = \"%1\", high = %2, low = %3, open = %4, "
            "close = %5, wap = %6, volume = %7, count = %8}")
            .arg(QString::fromStdString(time))
            .arg(high)
            .arg(low)
            .arg(open)
            .arg(close)
            .arg(wap) 
            .arg(volume) 
            .arg(count);
    }
};

#endif