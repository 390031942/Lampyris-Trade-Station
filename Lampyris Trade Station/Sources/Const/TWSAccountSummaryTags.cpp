/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

// Project Include(s)
#include "TWSAccountSummaryTags.h"
#include <Utility/StringUtil.h>

std::string TWSAccountSummaryTags::AccountType = "AccountType";
std::string TWSAccountSummaryTags::NetLiquidation = "NetLiquidation";
std::string TWSAccountSummaryTags::TotalCashValue = "TotalCashValue";
std::string TWSAccountSummaryTags::SettledCash = "SettledCash";
std::string TWSAccountSummaryTags::AccruedCash = "AccruedCash";
std::string TWSAccountSummaryTags::BuyingPower = "BuyingPower";
std::string TWSAccountSummaryTags::EquityWithLoanValue = "EquityWithLoanValue";
std::string TWSAccountSummaryTags::PreviousEquityWithLoanValue = "PreviousEquityWithLoanValue";
std::string TWSAccountSummaryTags::GrossPositionValue = "GrossPositionValue";
std::string TWSAccountSummaryTags::ReqTEquity = "ReqTEquity";
std::string TWSAccountSummaryTags::ReqTMargin = "ReqTMargin";
std::string TWSAccountSummaryTags::SMA = "SMA";
std::string TWSAccountSummaryTags::InitMarginReq = "InitMarginReq";
std::string TWSAccountSummaryTags::MaintMarginReq = "MaintMarginReq";
std::string TWSAccountSummaryTags::AvailableFunds = "AvailableFunds";
std::string TWSAccountSummaryTags::ExcessLiquidity = "ExcessLiquidity";
std::string TWSAccountSummaryTags::Cushion = "Cushion";
std::string TWSAccountSummaryTags::FullInitMarginReq = "FullInitMarginReq";
std::string TWSAccountSummaryTags::FullMaintMarginReq = "FullMaintMarginReq";
std::string TWSAccountSummaryTags::FullAvailableFunds = "FullAvailableFunds";
std::string TWSAccountSummaryTags::FullExcessLiquidity = "FullExcessLiquidity";
std::string TWSAccountSummaryTags::LookAheadNextChange = "LookAheadNextChange";
std::string TWSAccountSummaryTags::LookAheadInitMarginReq = "LookAheadInitMarginReq";
std::string TWSAccountSummaryTags::LookAheadMaintMarginReq = "LookAheadMaintMarginReq";
std::string TWSAccountSummaryTags::LookAheadAvailableFunds = "LookAheadAvailableFunds";
std::string TWSAccountSummaryTags::LookAheadExcessLiquidity = "LookAheadExcessLiquidity";
std::string TWSAccountSummaryTags::HighestSeverity = "HighestSeverity";
std::string TWSAccountSummaryTags::DayTradesRemaining = "DayTradesRemaining";
std::string TWSAccountSummaryTags::Leverage = "Leverage";

std::uint32_t TWSAccountSummaryTags::AccountTypeHash;
std::uint32_t TWSAccountSummaryTags::NetLiquidationHash;
std::uint32_t TWSAccountSummaryTags::TotalCashValueHash;
std::uint32_t TWSAccountSummaryTags::SettledCashHash;
std::uint32_t TWSAccountSummaryTags::AccruedCashHash;
std::uint32_t TWSAccountSummaryTags::BuyingPowerHash;
std::uint32_t TWSAccountSummaryTags::EquityWithLoanValueHash;
std::uint32_t TWSAccountSummaryTags::PreviousEquityWithLoanValueHash;
std::uint32_t TWSAccountSummaryTags::GrossPositionValueHash;
std::uint32_t TWSAccountSummaryTags::ReqTEquityHash;
std::uint32_t TWSAccountSummaryTags::ReqTMarginHash;
std::uint32_t TWSAccountSummaryTags::SMAHash;
std::uint32_t TWSAccountSummaryTags::InitMarginReqHash;
std::uint32_t TWSAccountSummaryTags::MaintMarginReqHash;
std::uint32_t TWSAccountSummaryTags::AvailableFundsHash;
std::uint32_t TWSAccountSummaryTags::ExcessLiquidityHash;
std::uint32_t TWSAccountSummaryTags::CushionHash;
std::uint32_t TWSAccountSummaryTags::FullInitMarginReqHash;
std::uint32_t TWSAccountSummaryTags::FullMaintMarginReqHash;
std::uint32_t TWSAccountSummaryTags::FullAvailableFundsHash;
std::uint32_t TWSAccountSummaryTags::FullExcessLiquidityHash;
std::uint32_t TWSAccountSummaryTags::LookAheadNextChangeHash;
std::uint32_t TWSAccountSummaryTags::LookAheadInitMarginReqHash;
std::uint32_t TWSAccountSummaryTags::LookAheadMaintMarginReqHash;
std::uint32_t TWSAccountSummaryTags::LookAheadAvailableFundsHash;
std::uint32_t TWSAccountSummaryTags::LookAheadExcessLiquidityHash;
std::uint32_t TWSAccountSummaryTags::HighestSeverityHash;
std::uint32_t TWSAccountSummaryTags::DayTradesRemainingHash;
std::uint32_t TWSAccountSummaryTags::LeverageHash;

bool TWSAccountSummaryTags::__hidden = TWSAccountSummaryTags::initHashValue();

std::string TWSAccountSummaryTags::getAllTags(){
	return AccountType + "," + NetLiquidation + "," + TotalCashValue + "," + SettledCash + "," + AccruedCash + "," + BuyingPower + "," + EquityWithLoanValue + "," + PreviousEquityWithLoanValue + "," + GrossPositionValue + "," + ReqTEquity
                + "," + ReqTMargin + "," + SMA + "," + InitMarginReq + "," + MaintMarginReq + "," + AvailableFunds + "," + ExcessLiquidity + "," + Cushion + "," + FullInitMarginReq + "," + FullMaintMarginReq + "," + FullAvailableFunds + "," + FullExcessLiquidity
                + "," + LookAheadNextChange + "," + LookAheadInitMarginReq + "," + LookAheadMaintMarginReq + "," + LookAheadAvailableFunds + "," + LookAheadExcessLiquidity + "," + HighestSeverity + "," + DayTradesRemaining + "," + Leverage;
}

bool TWSAccountSummaryTags::initHashValue(){
	AccountTypeHash = StringUtil::getHashCode(AccountType);
	NetLiquidationHash = StringUtil::getHashCode(NetLiquidation);
	TotalCashValueHash = StringUtil::getHashCode(TotalCashValue);
	SettledCashHash = StringUtil::getHashCode(SettledCash);
	AccruedCashHash = StringUtil::getHashCode(AccruedCash);
	BuyingPowerHash = StringUtil::getHashCode(BuyingPower);
	EquityWithLoanValueHash = StringUtil::getHashCode(EquityWithLoanValue);
	PreviousEquityWithLoanValueHash = StringUtil::getHashCode(PreviousEquityWithLoanValue);
	GrossPositionValueHash = StringUtil::getHashCode(GrossPositionValue);
	ReqTEquityHash = StringUtil::getHashCode(ReqTEquity);
	ReqTMarginHash = StringUtil::getHashCode(ReqTMargin);
	SMAHash = StringUtil::getHashCode(SMA);
	InitMarginReqHash = StringUtil::getHashCode(InitMarginReq);
	MaintMarginReqHash = StringUtil::getHashCode(MaintMarginReq);
	AvailableFundsHash = StringUtil::getHashCode(AvailableFunds);
	ExcessLiquidityHash = StringUtil::getHashCode(ExcessLiquidity);
	CushionHash = StringUtil::getHashCode(Cushion);
	FullInitMarginReqHash = StringUtil::getHashCode(FullInitMarginReq);
	FullMaintMarginReqHash = StringUtil::getHashCode(FullMaintMarginReq);
	FullAvailableFundsHash = StringUtil::getHashCode(FullAvailableFunds);
	FullExcessLiquidityHash = StringUtil::getHashCode(FullExcessLiquidity);
	LookAheadNextChangeHash = StringUtil::getHashCode(LookAheadNextChange);
	LookAheadInitMarginReqHash = StringUtil::getHashCode(LookAheadInitMarginReq);
	LookAheadMaintMarginReqHash = StringUtil::getHashCode(LookAheadMaintMarginReq);
	LookAheadAvailableFundsHash = StringUtil::getHashCode(LookAheadAvailableFunds);
	LookAheadExcessLiquidityHash = StringUtil::getHashCode(LookAheadExcessLiquidity);
	HighestSeverityHash = StringUtil::getHashCode(HighestSeverity);
	DayTradesRemainingHash = StringUtil::getHashCode(DayTradesRemaining);
	LeverageHash = StringUtil::getHashCode(Leverage);

    return true;
}

std::string TWSAccountSummaryTags::getConcernedTags() {
    return NetLiquidation + "," + GrossPositionValue + "," + AvailableFunds + "," + BuyingPower + "," +
           Leverage + "," + InitMarginReq + "," + MaintMarginReq + "," + DayTradesRemaining;
}
