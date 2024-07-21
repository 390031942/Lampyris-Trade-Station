/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/EnumManager.h>

enum TradeOrderType {
	Limit = 0,
	Market = 1,
};


/*
1.SMART-Smart Route:智能路由交易系统，由多个交易所和市场参与者组成，旨在提供最优的交易价格,
2.AMEX-American Stock Exchange: 美国证券交易所，现为纽约证券交易所的一部分。
3.ARCA-Archipelago Exchange: 群岛交易所，现为纽约证券交易所的一部分。
4.BATS-Bats Global Markets:全球市场交易所，提供股票交易服务，现已与CBOE合并。
5.BEX-Boston Stock Exchange: 波士顿证券交易所，现为纳斯达克的一部分。
6.BYX-BYX Exchange: 由波士顿期权交易所和波士顿股票交易所合并而成，现为纳斯达克的一部分。
7.CBOE-Chicago Board Options Exchange: 芝加哥期权交易所，提供期权交易服务。
8.CHX-Chicago Stock Exchange: 芝加哥股票交易所，提供股票交易服务。
9.DRCTEDGE-Direct Edge:直接边缘交易所，提供股票交易服务，现为纳斯达克的一部分。
10.EDGEA-EdgeA: 直接边缘交易所的另一部分，现已并入纳斯达克。
11,EDGX-EDGXExchanae;由Direct Edae运营的另一个交易所，提供股票交易服务,
12.IBKRTS-IBKR ATS: Interactive Brokers的替代交易系统，提供股票和期权交易服务。
13.EX-Investors Exchange: 投资者父易所，是一个股票父易所，以其数据隐松政策而闻名。
14.ISE-International Securities Exchange: 国际证券交易所，提供期权和股权衍生品交易服务。
15.ISLAND-lsland ECN: 岛屿电子通讯网络，是一个电子交易平台，现已并入纳斯达克
16.LTSE-Long-Term Stock Exchange:长期股票交易所，旨在鼓励长期投资和透明度。
17.MEMX-Members Exchange:成员交易所，是一个新成立的交易所，旨在提供更低成本的交易服务
18.NVSE-National Stock Exchange: 国家证券交易所，提供股票交易服务。
19.NYSENAT-New York Stock Exchange National:纽约证券交易所国家版，是纽约证券交易所的一部分。
20.PEARL-Pearl Exchange: 珍珠交易所，提供股票交易服务。
21.PHLX-Philadelphia Stock Exchange: 费城股票交易所，现为纳斯达克的一部分。
22.PSX-Pacific Stock Exchange:太平洋股票交易所，提供股票和期权交易服务，现已并入纽约证券交易所。
*/
enum TradeExchangeType {
	SMART = 0,
	AMEX = 1,
	ARCA = 2,
	BATS = 3,
	BEX = 4,
	BYX = 5,
	CBOE = 6,
	CHX = 7,
	DRCTEDGE = 8,
	EDGEA = 9,
	EDGX = 10,
	IBKRTS = 11,
	IEX = 12,
	ISE = 13,
	ISLAND = 14,
	LTSE = 15,
	MEMX = 16,
	NVSE = 17,
	NYSENAT = 18,
	PEARL = 19,
	PHLX = 20,
	PSX = 21,
};

enum TradeTIFType {
	DAY = 0, // 当日有效
	GTC = 1, // 取消前有效
	GTD = 2, // 到期前有效
};

// 子订单类型
enum TradeSubOrderType {
	None = 0,
	TakeProfit = 1, // 止盈
	StopLoss = 2, // 止损
	Both = 3, // 止盈+止损
};