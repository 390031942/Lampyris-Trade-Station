﻿/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_HISTORICALTICK_H
#define TWS_API_CLIENT_HISTORICALTICK_H

#include "Decimal.h"
#include <Base/TWSObject.h>

struct HistoricalTick:public TWSObject
{
    long long time;
    double price;
    Decimal size;

    virtual QString ToString() const override {
        return QString("{time = %1, price = %2, size = %3}")
            .arg(time).arg(price).arg(size);
    }
};  
#endif // !historicaltickendtry_def


