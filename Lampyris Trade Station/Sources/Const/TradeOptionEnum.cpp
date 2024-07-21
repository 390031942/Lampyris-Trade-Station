/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "TradeOptionEnum.h"

LAMPYRIS_DECLARE_ENUM_BEGIN(TradeOrderType)
{
	LAMPYRIS_ENUM_FIELD_LOCALIZED(Limit,  "TradeOrderType_Limit");
	LAMPYRIS_ENUM_FIELD_LOCALIZED(Market, "TradeOrderType_Market");
}
LAMPYRIS_DECLARE_ENUM_END;

// 注册 TradeExchangeType 枚举
LAMPYRIS_DECLARE_ENUM_BEGIN(TradeExchangeType) 
{
    LAMPYRIS_ENUM_FIELD_NO_DESC(SMART);
    LAMPYRIS_ENUM_FIELD_NO_DESC(AMEX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(ARCA);
    LAMPYRIS_ENUM_FIELD_NO_DESC(BATS);
    LAMPYRIS_ENUM_FIELD_NO_DESC(BEX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(BYX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(CBOE);
    LAMPYRIS_ENUM_FIELD_NO_DESC(CHX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(DRCTEDGE);
    LAMPYRIS_ENUM_FIELD_NO_DESC(EDGEA);
    LAMPYRIS_ENUM_FIELD_NO_DESC(EDGX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(IBKRTS);
    LAMPYRIS_ENUM_FIELD_NO_DESC(IEX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(ISE);
    LAMPYRIS_ENUM_FIELD_NO_DESC(ISLAND);
    LAMPYRIS_ENUM_FIELD_NO_DESC(LTSE);
    LAMPYRIS_ENUM_FIELD_NO_DESC(MEMX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(NVSE);
    LAMPYRIS_ENUM_FIELD_NO_DESC(NYSENAT);
    LAMPYRIS_ENUM_FIELD_NO_DESC(PEARL);
    LAMPYRIS_ENUM_FIELD_NO_DESC(PHLX);
    LAMPYRIS_ENUM_FIELD_NO_DESC(PSX);
}
LAMPYRIS_DECLARE_ENUM_END;

LAMPYRIS_DECLARE_ENUM_BEGIN(TradeTIFType)
{
    LAMPYRIS_ENUM_FIELD_LOCALIZED(DAY, "TradeTIFType_DAY"); // 当日有效
    LAMPYRIS_ENUM_FIELD_LOCALIZED(GTC, "TradeTIFType_GTC"); // 取消前有效
    LAMPYRIS_ENUM_FIELD_LOCALIZED(GTD, "TradeTIFType_GTD"); // 到期前有效
}
LAMPYRIS_DECLARE_ENUM_END;

LAMPYRIS_DECLARE_ENUM_BEGIN(TradeSubOrderType)
{
    LAMPYRIS_ENUM_FIELD_LOCALIZED(None, "TradeSubOrderType_None");
    LAMPYRIS_ENUM_FIELD_LOCALIZED(TakeProfit, "TradeSubOrderType_TakeProfit"); // 止盈
    LAMPYRIS_ENUM_FIELD_LOCALIZED(StopLoss, "TradeSubOrderType_StopLoss"); // 止损
    LAMPYRIS_ENUM_FIELD_LOCALIZED(Both, "TradeSubOrderType_Both"); // 止盈+止损
}
LAMPYRIS_DECLARE_ENUM_END;