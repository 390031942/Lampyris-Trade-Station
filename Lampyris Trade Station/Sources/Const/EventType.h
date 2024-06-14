/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

enum class EventType {
    // 价格跳动事件
    TWS_TICK_PRICE = 10001, // tickPrice
    // 市场深度大小跳动事件
    TWS_TICK_SIZE = 10002, // tickSize
    // 期权计算数据跳动事件
    TWS_TICK_OPTION_COMPUTATION = 10003, // tickOptionComputation
    // 通用数据跳动事件
    TWS_TICK_GENERIC = 10004, // tickGeneric
    // 字符串数据跳动事件
    TWS_TICK_STRING = 10005, // tickString
    // EFP数据跳动事件
    TWS_TICK_EFP = 10006, // tickEFP
    // 订单状态更新事件
    TWS_ORDER_STATUS = 10007, // orderStatus
    // 打开订单事件
    TWS_OPEN_ORDER = 10008, // openOrder
    // 打开订单结束事件
    TWS_OPEN_ORDER_END = 10009, // openOrderEnd
    // 错误事件
    TWS_WIN_ERROR = 10010, // winError
    // 连接关闭事件
    TWS_CONNECTION_CLOSED = 10011, // connectionClosed
    // 账户值更新事件
    TWS_UPDATE_ACCOUNT_VALUE = 10012, // updateAccountValue
    // 投资组合更新事件
    TWS_UPDATE_PORTFOLIO = 10013, // updatePortfolio
    // 账户时间更新事件
    TWS_UPDATE_ACCOUNT_TIME = 10014, // updateAccountTime
    // 账户下载结束事件
    TWS_ACCOUNT_DOWNLOAD_END = 10015, // accountDownloadEnd
    // 下一个有效订单ID事件
    TWS_NEXT_VALID_ID = 10016, // nextValidId
    // 合约详情事件
    TWS_CONTRACT_DETAILS = 10017, // contractDetails
    // 债券合约详情事件
    TWS_BOND_CONTRACT_DETAILS = 10018, // bondContractDetails
    // 合约详情结束事件
    TWS_CONTRACT_DETAILS_END = 10019, // contractDetailsEnd
    // 执行详情事件
    TWS_EXEC_DETAILS = 10020, // execDetails
    // 执行详情结束事件
    TWS_EXEC_DETAILS_END = 10021, // execDetailsEnd
    // 错误信息事件
    TWS_ERROR = 10022, // error
    // 市场深度更新事件
    TWS_UPDATE_MKT_DEPTH = 10023, // updateMktDepth
    // 市场深度L2更新事件
    TWS_UPDATE_MKT_DEPTH_L2 = 10024, // updateMktDepthL2
    // 新闻公告事件
    TWS_UPDATE_NEWS_BULLETIN = 10025, // updateNewsBulletin
    // 管理账户列表事件
    TWS_MANAGED_ACCOUNTS = 10026, // managedAccounts
    // 接收FA数据事件
    TWS_RECEIVE_FA = 10027, // receiveFA
    // 历史数据事件
    TWS_HISTORICAL_DATA = 10028, // historicalData
    // 历史数据结束事件
    TWS_HISTORICAL_DATA_END = 10029, // historicalDataEnd
    // 扫描参数事件
    TWS_SCANNER_PARAMETERS = 10030, // scannerParameters
    // 扫描数据事件
    TWS_SCANNER_DATA = 10031, // scannerData
    // 扫描数据结束事件
    TWS_SCANNER_DATA_END = 10032, // scannerDataEnd
    // 实时条形图数据事件
    TWS_REAL_TIME_BARS = 10033, // realtimeBar
    // 当前时间事件
    TWS_CURRENT_TIME = 10034, // currentTime
    // 基本面数据事件
    TWS_FUNDAMENTAL_DATA = 10035, // fundamentalData
    // 德尔塔中性验证事件
    TWS_DELTA_NEUTRAL_VALIDATION = 10036, // deltaNeutralValidation
    // 快照数据结束事件
    TWS_TICK_SNAPSHOT_END = 10037, // tickSnapshotEnd
    // 市场数据类型事件
    TWS_MARKET_DATA_TYPE = 10038, // marketDataType
    // 佣金报告事件
    TWS_COMMISSION_REPORT = 10039, // commissionReport
    // 持仓更新事件
    TWS_POSITION = 10040, // position
    // 持仓更新结束事件
    TWS_POSITION_END = 10041, // positionEnd
    // 账户摘要更新事件
    TWS_ACCOUNT_SUMMARY = 10042, // accountSummary
    // 账户摘要更新结束事件
    TWS_ACCOUNT_SUMMARY_END = 10043, // accountSummaryEnd
    // 验证消息API事件
    TWS_VERIFY_MESSAGE_API = 10044, // verifyMessageAPI
    // 验证完成事件
    TWS_VERIFY_COMPLETED = 10045, // verifyCompleted
    // 显示组列表事件
    TWS_DISPLAY_GROUP_LIST = 10046, // displayGroupList
    // 显示组更新事件
    TWS_DISPLAY_GROUP_UPDATED = 10047, // displayGroupUpdated
    // 验证并授权消息API事件
    TWS_VERIFY_AND_AUTH_MESSAGE_API = 10048, // verifyAndAuthMessageAPI
    // 验证并授权完成事件
    TWS_VERIFY_AND_AUTH_COMPLETED = 10049, // verifyAndAuthCompleted
    // 连接确认事件
    TWS_CONNECT_ACK = 10050, // connectAck
    // 多账户持仓更新事件
    TWS_POSITION_MULTI = 10051, // positionMulti
    // 多账户持仓更新结束事件
    TWS_POSITION_MULTI_END = 10052, // positionMultiEnd
    // 多账户更新事件
    TWS_ACCOUNT_UPDATE_MULTI = 10053, // accountUpdateMulti
    // 多账户更新结束事件
    TWS_ACCOUNT_UPDATE_MULTI_END = 10054, // accountUpdateMultiEnd
    // 证券定义可选参数事件
    TWS_SECURITY_DEFINITION_OPTIONAL_PARAMETER = 10055, // securityDefinitionOptionalParameter
    // 证券定义可选参数结束事件
    TWS_SECURITY_DEFINITION_OPTIONAL_PARAMETER_END = 10056, // securityDefinitionOptionalParameterEnd
    // 软美元层级事件
    TWS_SOFT_DOLLAR_TIERS = 10057, // softDollarTiers
    // 家族代码事件
    TWS_FAMILY_CODES = 10058, // familyCodes
    // 符号样本事件
    TWS_SYMBOL_SAMPLES = 10059, // symbolSamples
    // 市场深度交易所事件
    TWS_MKT_DEPTH_EXCHANGES = 10060, // mktDepthExchanges
    // 市场数据新闻事件
    TWS_TICK_NEWS = 10061, // tickNews
    // 智能组件事件
    TWS_SMART_COMPONENTS = 10062, // smartComponents
    // 市场数据请求参数事件
    TWS_TICK_REQ_PARAMS = 10063, // tickReqParams
    // 新闻提供者列表事件
    TWS_NEWS_PROVIDERS = 10064, // newsProviders
    // 新闻文章事件
    TWS_NEWS_ARTICLE = 10065, // newsArticle
    // 历史新闻事件
    TWS_HISTORICAL_NEWS = 10066, // historicalNews
    // 历史新闻结束事件
    TWS_HISTORICAL_NEWS_END = 10067, // historicalNewsEnd
    // 头部时间戳事件
    TWS_HEAD_TIMESTAMP = 10068, // headTimestamp
    // 直方图数据事件
    TWS_HISTOGRAM_DATA = 10069, // histogramData
    // 历史数据更新事件
    TWS_HISTORICAL_DATA_UPDATE = 10070, // historicalDataUpdate
    // 重定向市场数据请求事件
    TWS_REROUTE_MKT_DATA_REQ = 10071, // rerouteMktDataReq
    // 重定向市场深度请求事件
    TWS_REROUTE_MKT_DEPTH_REQ = 10072, // rerouteMktDepthReq
    // 市场规则事件
    TWS_MARKET_RULE = 10073, // marketRule
    // PnL更新事件
    TWS_PNL = 10074, // pnl
    // 单一PnL更新事件
    TWS_PNL_SINGLE = 10075, // pnlSingle
    // 历史Tick数据事件
    TWS_HISTORICAL_TICKS = 10076, // historicalTicks
    // 历史BidAsk Tick数据事件
    TWS_HISTORICAL_TICKS_BID_ASK = 10077,
    // 历史BidAsk Tick数据事件
    TWS_HISTORICAL_TICKS_BID_ASK = 10078, // historicalTicksBidAsk
    // 历史Last Tick数据事件
    TWS_HISTORICAL_TICKS_LAST = 10079, // historicalTicksLast
    // Tick by Tick 全部最后数据事件
    TWS_TICK_BY_TICK_ALL_LAST = 10080, // tickByTickAllLast
    // Tick by Tick 买卖数据事件
    TWS_TICK_BY_TICK_BID_ASK = 10081, // tickByTickBidAsk
    // Tick by Tick 中点数据事件
    TWS_TICK_BY_TICK_MID_POINT = 10082, // tickByTickMidPoint
    // 订单绑定事件
    TWS_ORDER_BOUND = 10083, // orderBound
    // 完成订单事件
    TWS_COMPLETED_ORDER = 10084, // completedOrder
    // 完成订单结束事件
    TWS_COMPLETED_ORDERS_END = 10085, // completedOrdersEnd
    // 替换FA结束事件
    TWS_REPLACE_FA_END = 10086, // replaceFAEnd
    // WS手数据元数据事件
    TWS_WSH_METADATA = 10087, // wshMetaData
    // WS手事件数据事件
    TWS_WSH_EVENT_DATA = 10088, // wshEventData
    // 历史时间表事件
    TWS_HISTORICAL_SCHEDULE = 10089, // historicalSchedule
    // 用户信息事件
    TWS_USER_INFO = 10090 // userInfo
};
