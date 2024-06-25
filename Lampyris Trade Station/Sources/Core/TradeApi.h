/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <string>

// Project Include(s)
#include <Base/Singleton.h>

class TradeApi {
public:
	void buy(const std::string& code,float price,float count);

	void sell(const std::string& code, float price, float count);

	void shortBuy(const std::string& code, float price, float count);

	void shortSell(const std::string& code, float price, float count);

	void cancelOrder();

	void queryPosition();

	void queryTodayPnl();

	void queryTodayOrder();

	void queryTodayDealDetail();

private:
	void bindEvent();

	long m_nextValidOrderId;
};