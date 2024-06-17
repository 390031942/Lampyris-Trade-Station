/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_ORDERSTATE_H
#define TWS_API_CLIENT_ORDERSTATE_H

#include "Order.h"
#include <Base/TWSObject.h>

struct OrderState:public TWSObject {

	explicit OrderState()
		:
		commission(UNSET_DOUBLE),
		minCommission(UNSET_DOUBLE),
		maxCommission(UNSET_DOUBLE)
	{}

	std::string status;

	std::string initMarginBefore;
	std::string maintMarginBefore;
	std::string equityWithLoanBefore;
	std::string initMarginChange;
	std::string maintMarginChange;
	std::string equityWithLoanChange;
	std::string initMarginAfter;
	std::string maintMarginAfter;
	std::string equityWithLoanAfter;

	double  commission;
	double  minCommission;
	double  maxCommission;
	std::string commissionCurrency;

	std::string warningText;

	std::string completedTime;
	std::string completedStatus;

    virtual QString ToString() const override {
        return QString("{status: %1, initMarginBefore: %2, "
            "maintMarginBefore: %3, equityWithLoanBefore: %4, "
            "initMarginChange: %5, maintMarginChange: %6, "
            "equityWithLoanChange: %7, initMarginAfter: %8, "
            "maintMarginAfter: %9, equityWithLoanAfter: %10, "
            "commission: %11, minCommission: %12, maxCommission: %13, "
            "commissionCurrency: %14, warningText: %15, "
            "completedTime: %16, completedStatus: %17}")
            .arg(QString::fromStdString(status))
            .arg(QString::fromStdString(initMarginBefore))
            .arg(QString::fromStdString(maintMarginBefore))
            .arg(QString::fromStdString(equityWithLoanBefore))
            .arg(QString::fromStdString(initMarginChange))
            .arg(QString::fromStdString(maintMarginChange))
            .arg(QString::fromStdString(equityWithLoanChange))
            .arg(QString::fromStdString(initMarginAfter))
            .arg(QString::fromStdString(maintMarginAfter))
            .arg(QString::fromStdString(equityWithLoanAfter))
            .arg(commission)
            .arg(minCommission)
            .arg(maxCommission)
            .arg(QString::fromStdString(commissionCurrency))
            .arg(QString::fromStdString(warningText))
            .arg(QString::fromStdString(completedTime))
            .arg(QString::fromStdString(completedStatus));
    }
};

#endif
