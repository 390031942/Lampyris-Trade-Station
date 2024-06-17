/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_SOFTDOLLARTIER_H
#define TWS_API_CLIENT_SOFTDOLLARTIER_H

#include "platformspecific.h"
#include <string>
#include <Base/TWSObject.h>

class TWSAPIDLLEXP SoftDollarTier:public TWSObject
{
	std::string m_name, m_val, m_displayName;

public:
	SoftDollarTier(const std::string& name = "", const std::string& val = "", const std::string& displayName = "");

	std::string name() const;
	std::string val() const;
	std::string displayName() const;

	virtual QString ToString() const override {
		return QString("{name: %1, val: %2, displayName: %3")
			.arg(m_name.c_str()).arg(m_val.c_str()).arg(m_displayName.c_str());
	}
};

#endif