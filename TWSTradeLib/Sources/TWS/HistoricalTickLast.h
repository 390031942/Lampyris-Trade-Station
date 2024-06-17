/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_HISTORICALTICKLAST_H
#define TWS_API_CLIENT_HISTORICALTICKLAST_H

#include "TickAttribLast.h"
#include "Decimal.h"
#include <string>
#include <Base/TWSObject.h>

struct HistoricalTickLast :public TWSObject
{
    long long time;
    TickAttribLast tickAttribLast;
    double price;
    Decimal size;
    std::string exchange;
    std::string specialConditions;

    virtual QString ToString() const override {
        return QString("{time = %1, tickAttribLast = %2, price = %3, size = %4, exchange = %5, specialConditions = %6 }")
            .arg(time).arg(tickAttribLast.ToString()).arg(price)
            .arg(size).arg(exchange.c_str()).arg(specialConditions.c_str());
    }
};
#endif

