/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EWRAPPER_H
#define TWS_API_CLIENT_EWRAPPER_H

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include "CommonDefs.h"
#include "SoftDollarTier.h"
#include "DepthMktDataDescription.h"
#include "FamilyCode.h"
#include "NewsProvider.h"
#include "TickAttrib.h"
#include "HistogramEntry.h"
#include "bar.h"
#include "PriceIncrement.h"
#include "HistoricalTick.h"
#include "HistoricalTickBidAsk.h"
#include "HistoricalTickLast.h"
#include "Decimal.h"
#include "HistoricalSession.h"

/*
 * 以下注释 不一定准确
*/
enum TickType {
    BID_SIZE,             // 竞买价的订单数量
    BID,                  // 竞买价
    ASK,                  // 竞卖价
    ASK_SIZE,             // 竞卖价的订单数量
    LAST,                 // 最后成交价
    LAST_SIZE,            // 最后成交的数量
    HIGH,                 // 当日最高价
    LOW,                  // 当日最低价
    VOLUME,               // 成交量
    CLOSE,                // 收盘价
    BID_OPTION_COMPUTATION, // 期权竞买价计算值
    ASK_OPTION_COMPUTATION, // 期权竞卖价计算值
    LAST_OPTION_COMPUTATION, // 期权最后成交价计算值
    MODEL_OPTION,         // 期权模型价
    OPEN,                 // 开盘价
    LOW_13_WEEK,          // 13周最低价
    HIGH_13_WEEK,         // 13周最高价
    LOW_26_WEEK,          // 26周最低价
    HIGH_26_WEEK,         // 26周最高价
    LOW_52_WEEK,          // 52周最低价
    HIGH_52_WEEK,         // 52周最高价
    AVG_VOLUME,           // 平均成交量
    OPEN_INTEREST,        // 未平仓合约数
    OPTION_HISTORICAL_VOL, // 期权历史波动率
    OPTION_IMPLIED_VOL,   // 期权隐含波动率
    OPTION_BID_EXCH,     // 期权竞买价交易所
    OPTION_ASK_EXCH,     // 期权竞卖价交易所
    OPTION_CALL_OPEN_INTEREST, // 期权看涨未平仓合约数
    OPTION_PUT_OPEN_INTEREST, // 期权看跌未平仓合约数
    OPTION_CALL_VOLUME,  // 期权看涨成交量
    OPTION_PUT_VOLUME,   // 期权看跌成交量
    INDEX_FUTURE_PREMIUM, // 股指期货溢价
    BID_EXCH,            // 竞买价交易所
    ASK_EXCH,            // 竞卖价交易所
    AUCTION_VOLUME,       // 拍卖成交量
    AUCTION_PRICE,        // 拍卖价格
    AUCTION_IMBALANCE,    // 拍卖不平衡量
    MARK_PRICE,          // 标记价格
    BID_EFP_COMPUTATION,  // EFP竞买价计算
    ASK_EFP_COMPUTATION,  // EFP竞卖价计算
    LAST_EFP_COMPUTATION, // EFP最后成交价计算
    OPEN_EFP_COMPUTATION, // EFP开盘价计算
    HIGH_EFP_COMPUTATION, // EFP最高价计算
    LOW_EFP_COMPUTATION,  // EFP最低价计算
    CLOSE_EFP_COMPUTATION,// EFP收盘价计算
    LAST_TIMESTAMP,      // 最后成交时间戳
    SHORTABLE,           // 是否可卖空
    FUNDAMENTAL_RATIOS,   // 基本面比率
    RT_VOLUME,           // 实时成交量
    HALTED,              // 是否暂停交易
    BID_YIELD,           // 竞买收益率
    ASK_YIELD,           // 竞卖收益率
    LAST_YIELD,          // 最后成交收益率
    CUST_OPTION_COMPUTATION, // 定制期权计算
    TRADE_COUNT,         // 成交计数
    TRADE_RATE,          // 成交速率
    VOLUME_RATE,         // 成交量速率
    LAST_RTH_TRADE,      // 最后一个交易日的成交
    RT_HISTORICAL_VOL,   // 实时历史波动率
    IB_DIVIDENDS,        // IB股息
    BOND_FACTOR_MULTIPLIER, // 债券因子乘数
    REGULATORY_IMBALANCE, // 监管不平衡
    NEWS_TICK,           // 新闻行情
    SHORT_TERM_VOLUME_3_MIN, // 3分钟短期成交量
    SHORT_TERM_VOLUME_5_MIN, // 5分钟短期成交量
    SHORT_TERM_VOLUME_10_MIN, // 10分钟短期成交量
    DELAYED_BID,         // 延迟竞买价
    DELAYED_ASK,         // 延迟竞卖价
    DELAYED_LAST,        // 延迟最后成交价
    DELAYED_BID_SIZE,    // 延迟竞买订单数量
    DELAYED_ASK_SIZE,    // 延迟竞卖订单数量
    DELAYED_LAST_SIZE,   // 延迟最后成交数量
    DELAYED_HIGH,        // 延迟当日最高价
    DELAYED_LOW,          // 延迟当日最低价
    DELAYED_VOLUME,       // 延迟成交量
    DELAYED_CLOSE,        // 延迟收盘价
    DELAYED_OPEN,         // 延迟开盘价
    RT_TRD_VOLUME,        // 实时交易量
    CREDITMAN_MARK_PRICE,  // 信贷管理标记价格
    CREDITMAN_SLOW_MARK_PRICE, // 信贷管理慢速标记价格
    DELAYED_BID_OPTION_COMPUTATION, // 延迟期权竞买价计算值
    DELAYED_ASK_OPTION_COMPUTATION, // 延迟期权竞卖价计算值
    DELAYED_LAST_OPTION_COMPUTATION, // 延迟期权最后成交价计算值
    DELAYED_MODEL_OPTION_COMPUTATION, // 延迟期权模型价计算
    LAST_EXCH,            // 最后成交交易所
    LAST_REG_TIME,        // 最后规定时间
    FUTURES_OPEN_INTEREST, // 期货未平仓合约数
    AVG_OPT_VOLUME,       // 平均期权成交量
    DELAYED_LAST_TIMESTAMP, // 延迟最后成交时间戳
    SHORTABLE_SHARES,     // 可卖空股份
    DELAYED_HALTED,       // 延迟暂停交易状态
    REUTERS_2_MUTUAL_FUNDS, // 路透社2共同基金
    ETF_NAV_CLOSE,        // ETF净资产价值收盘价
    ETF_NAV_PRIOR_CLOSE,  // ETF净资产价值前收盘价
    ETF_NAV_BID,          // ETF净资产价值竞买价
    ETF_NAV_ASK,          // ETF净资产价值竞卖价
    ETF_NAV_LAST,         // ETF净资产价值最后成交价
    ETF_FROZEN_NAV_LAST,  // ETF冻结的净资产价值最后成交价
    ETF_NAV_HIGH,         // ETF净资产价值当日最高价
    ETF_NAV_LOW,          // ETF净资产价值当日最低价
    SOCIAL_MARKET_ANALYTICS, // 社交市场分析
    ESTIMATED_IPO_MIDPOINT, // 预估IPO中点价格
    FINAL_IPO_LAST,       // 最终IPO最后成交价
    NOT_SET               // 未设置
};

typedef std::map<int, std::tuple<std::string, char>> SmartComponentsMap;
typedef std::vector<HistogramEntry> HistogramDataVector;


inline bool isPrice( TickType tickType) {
	return tickType == BID || tickType == ASK || tickType == LAST || tickType == DELAYED_BID || tickType == DELAYED_ASK || tickType == DELAYED_LAST;
}

struct Contract;
struct ContractDetails;
struct ContractDescription;
struct Order;
struct OrderState;
struct Execution;
struct DeltaNeutralContract;
struct CommissionReport;

class EWrapper
{
public:
   virtual ~EWrapper() {};

	#define EWRAPPER_VIRTUAL_IMPL {}
	#include "EWrapper_prototypes.h"
};


#endif
