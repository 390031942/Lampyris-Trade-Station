/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_SAMPLES_TESTCPPCLIENT_ACCOUNTSUMMARYTAGS_H
#define TWS_API_SAMPLES_TESTCPPCLIENT_ACCOUNTSUMMARYTAGS_H

// Project Include(s)
#include <string>

class TWSAccountSummaryTags{
private:
	static bool        __hidden;
	static bool        initHashValue();
public:
	static std::string AccountType;
    static std::string NetLiquidation;
    static std::string TotalCashValue;
    static std::string SettledCash;
    static std::string AccruedCash;
    static std::string BuyingPower;
    static std::string EquityWithLoanValue;
    static std::string PreviousEquityWithLoanValue;
    static std::string GrossPositionValue;
    static std::string ReqTEquity;
    static std::string ReqTMargin;
    static std::string SMA;
    static std::string InitMarginReq;
    static std::string MaintMarginReq;
    static std::string AvailableFunds;
    static std::string ExcessLiquidity;
    static std::string Cushion;
    static std::string FullInitMarginReq;
    static std::string FullMaintMarginReq;
    static std::string FullAvailableFunds;
    static std::string FullExcessLiquidity;
    static std::string LookAheadNextChange;
    static std::string LookAheadInitMarginReq;
    static std::string LookAheadMaintMarginReq;
    static std::string LookAheadAvailableFunds;
    static std::string LookAheadExcessLiquidity;
    static std::string HighestSeverity;
    static std::string DayTradesRemaining;
    static std::string Leverage;

	static std::uint32_t AccountTypeHash;
	static std::uint32_t NetLiquidationHash;
	static std::uint32_t TotalCashValueHash;
	static std::uint32_t SettledCashHash;
	static std::uint32_t AccruedCashHash;
	static std::uint32_t BuyingPowerHash;
	static std::uint32_t EquityWithLoanValueHash;
	static std::uint32_t PreviousEquityWithLoanValueHash;
	static std::uint32_t GrossPositionValueHash;
	static std::uint32_t ReqTEquityHash;
	static std::uint32_t ReqTMarginHash;
	static std::uint32_t SMAHash;
	static std::uint32_t InitMarginReqHash;
	static std::uint32_t MaintMarginReqHash;
	static std::uint32_t AvailableFundsHash;
	static std::uint32_t ExcessLiquidityHash;
	static std::uint32_t CushionHash;
	static std::uint32_t FullInitMarginReqHash;
	static std::uint32_t FullMaintMarginReqHash;
	static std::uint32_t FullAvailableFundsHash;
	static std::uint32_t FullExcessLiquidityHash;
	static std::uint32_t LookAheadNextChangeHash;
	static std::uint32_t LookAheadInitMarginReqHash;
	static std::uint32_t LookAheadMaintMarginReqHash;
	static std::uint32_t LookAheadAvailableFundsHash;
	static std::uint32_t LookAheadExcessLiquidityHash;
	static std::uint32_t HighestSeverityHash;
	static std::uint32_t DayTradesRemainingHash;
	static std::uint32_t LeverageHash;

	static std::string getAllTags();
	static std::string getConcernedTags();
};

#endif