/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_COMMISSIONREPORT_H
#define TWS_API_CLIENT_COMMISSIONREPORT_H

#include <string>
#include <Base/TWSObject.h>

struct CommissionReport:public TWSObject
{
	CommissionReport()
	{
		commission = 0;
		realizedPNL = 0;
		yield = 0;
		yieldRedemptionDate = 0;
	}

	// commission report fields
	std::string	execId;
	double		commission;
	std::string	currency;
	double		realizedPNL;
	double		yield;
	int			yieldRedemptionDate; // YYYYMMDD format

	virtual QString ToString() const override {
		return QString("{execId = \"%1\", commission = %2, currency = \"%3\", "
			"realizedPNL = %4, yield = %5, yieldRedemptionDate = %6}")
			.arg(QString::fromStdString(execId))
			.arg(commission)
			.arg(QString::fromStdString(currency))
			.arg(realizedPNL)
			.arg(yield)
			.arg(yieldRedemptionDate);
	}
};

#endif // commissionreport_def
