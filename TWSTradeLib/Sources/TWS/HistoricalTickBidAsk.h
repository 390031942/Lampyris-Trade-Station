/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_HISTORICALTICKBIDASK_H
#define TWS_API_CLIENT_HISTORICALTICKBIDASK_H

#include "TickAttribBidAsk.h"
#include "Decimal.h"
#include <Base/TWSObject.h>

struct HistoricalTickBidAsk:public TWSObject
{
    long long time;
    TickAttribBidAsk tickAttribBidAsk;
    double priceBid;
    double priceAsk;
    Decimal sizeBid;
    Decimal sizeAsk;

    virtual QString ToString() const override {
        return QString("{time = %1, tickAttribBidAsk = %2, priceBid = %3, priceAsk = %4, sizeBid = %5, sizeAsk = %6 }")
            .arg(time).arg(tickAttribBidAsk.ToString()).arg(priceBid)
            .arg(priceAsk).arg(sizeBid).arg(sizeAsk);
    }
};
#endif

