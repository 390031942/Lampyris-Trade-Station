/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EXECUTION_H
#define TWS_API_CLIENT_EXECUTION_H

#include <string>
#include "Decimal.h"
#include <Base/TWSObject.h>

struct Execution:public TWSObject
{
	Execution()
	{
		shares = 0;
		price = 0;
		permId = 0;
		clientId = 0;
		orderId = 0;
		cumQty = 0;
		avgPrice = 0;
		evMultiplier = 0;
        lastLiquidity = 0;
	}

	std::string	execId;
	std::string	time;
	std::string	acctNumber;
	std::string	exchange;
	std::string	side;
	Decimal 	shares;
	double		price;
	int			permId;
	long		clientId;
	long		orderId;
	int			liquidation;
	Decimal		cumQty;
	double		avgPrice;
	std::string	orderRef;
	std::string	evRule;
	double		evMultiplier;
	std::string modelCode;
    int         lastLiquidity;

	virtual QString ToString() const override {
		return QString("{execId: %1, time: %2, acctNumber: %3, "
			"exchange: %4, side: %5, shares: %6, price: %7, "
			"permId: %8, clientId: %9, orderId: %10, "
			"liquidation: %11, cumQty: %12, avgPrice: %13, "
			"orderRef: %14, evRule: %15, evMultiplier: %16, "
			"modelCode: %17, lastLiquidity: %18}")
			.arg(QString::fromStdString(execId))
			.arg(QString::fromStdString(time))
			.arg(QString::fromStdString(acctNumber))
			.arg(QString::fromStdString(exchange))
			.arg(QString::fromStdString(side))
			.arg(QString::number(shares))
			.arg(price)
			.arg(permId)
			.arg(clientId)
			.arg(orderId)
			.arg(liquidation)
			.arg(QString::number(cumQty))
			.arg(avgPrice)
			.arg(QString::fromStdString(orderRef))
			.arg(QString::fromStdString(evRule))
			.arg(evMultiplier)
			.arg(QString::fromStdString(modelCode))
			.arg(lastLiquidity);
	}
};

struct ExecutionFilter
{
	ExecutionFilter()
		: m_clientId(0)
	{
	}

	// Filter fields
	long		m_clientId;
	std::string	m_acctCode;
	std::string	m_time;
	std::string	m_symbol;
	std::string	m_secType;
	std::string	m_exchange;
	std::string	m_side;
};

#endif // execution_def
