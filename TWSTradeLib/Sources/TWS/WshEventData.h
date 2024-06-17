/* Copyright (C) 2022 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_WSHEVENTDATA_H
#define TWS_API_CLIENT_WSHEVENTDATA_H

#include <string>
#include <Base/TWSObject.h>

struct WshEventData :public TWSObject
{
	int conId;
	std::string filter;
	bool fillWatchlist;
	bool fillPortfolio;
	bool fillCompetitors;
	std::string startDate;
	std::string endDate;
	int totalLimit;

	WshEventData(int conId, bool fillWatchlist, bool fillPortfolio, bool fillCompetitors, std::string startDate, std::string endDate, int totalLimit)
	{
		this->conId = conId;
		this->filter = "";
		this->fillWatchlist = fillWatchlist;
		this->fillPortfolio = fillPortfolio;
		this->fillCompetitors = fillCompetitors;
		this->startDate = startDate;
		this->endDate = endDate;
		this->totalLimit = totalLimit;
	}

	WshEventData(std::string filter, bool fillWatchlist, bool fillPortfolio, bool fillCompetitors, std::string startDate, std::string endDate, int totalLimit)
	{
		this->conId = INT_MAX;
		this->filter = filter;
		this->fillWatchlist = fillWatchlist;
		this->fillPortfolio = fillPortfolio;
		this->fillCompetitors = fillCompetitors;
		this->startDate = startDate;
		this->endDate = endDate;
		this->totalLimit = totalLimit;
	}

	virtual QString ToString() const override {
		return QString("{conId = %1, filter = %2, fillWatchlist = %3, fillPortfolio = %4, fillCompetitors = %5, "
			"startDate = %6, endDate = %7, totalLimit = %8}")
			.arg(conId).arg(filter.c_str()).arg(fillWatchlist).arg(fillPortfolio).arg(fillCompetitors)
			.arg(startDate.c_str()).arg(endDate.c_str()).arg(totalLimit);
	}
};

#endif // wsheventdata_def