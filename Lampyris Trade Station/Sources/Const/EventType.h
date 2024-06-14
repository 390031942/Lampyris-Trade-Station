/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

enum class EventType {
    // �۸������¼�
    TWS_TICK_PRICE = 10001, // tickPrice
    // �г���ȴ�С�����¼�
    TWS_TICK_SIZE = 10002, // tickSize
    // ��Ȩ�������������¼�
    TWS_TICK_OPTION_COMPUTATION = 10003, // tickOptionComputation
    // ͨ�����������¼�
    TWS_TICK_GENERIC = 10004, // tickGeneric
    // �ַ������������¼�
    TWS_TICK_STRING = 10005, // tickString
    // EFP���������¼�
    TWS_TICK_EFP = 10006, // tickEFP
    // ����״̬�����¼�
    TWS_ORDER_STATUS = 10007, // orderStatus
    // �򿪶����¼�
    TWS_OPEN_ORDER = 10008, // openOrder
    // �򿪶��������¼�
    TWS_OPEN_ORDER_END = 10009, // openOrderEnd
    // �����¼�
    TWS_WIN_ERROR = 10010, // winError
    // ���ӹر��¼�
    TWS_CONNECTION_CLOSED = 10011, // connectionClosed
    // �˻�ֵ�����¼�
    TWS_UPDATE_ACCOUNT_VALUE = 10012, // updateAccountValue
    // Ͷ����ϸ����¼�
    TWS_UPDATE_PORTFOLIO = 10013, // updatePortfolio
    // �˻�ʱ������¼�
    TWS_UPDATE_ACCOUNT_TIME = 10014, // updateAccountTime
    // �˻����ؽ����¼�
    TWS_ACCOUNT_DOWNLOAD_END = 10015, // accountDownloadEnd
    // ��һ����Ч����ID�¼�
    TWS_NEXT_VALID_ID = 10016, // nextValidId
    // ��Լ�����¼�
    TWS_CONTRACT_DETAILS = 10017, // contractDetails
    // ծȯ��Լ�����¼�
    TWS_BOND_CONTRACT_DETAILS = 10018, // bondContractDetails
    // ��Լ��������¼�
    TWS_CONTRACT_DETAILS_END = 10019, // contractDetailsEnd
    // ִ�������¼�
    TWS_EXEC_DETAILS = 10020, // execDetails
    // ִ����������¼�
    TWS_EXEC_DETAILS_END = 10021, // execDetailsEnd
    // ������Ϣ�¼�
    TWS_ERROR = 10022, // error
    // �г���ȸ����¼�
    TWS_UPDATE_MKT_DEPTH = 10023, // updateMktDepth
    // �г����L2�����¼�
    TWS_UPDATE_MKT_DEPTH_L2 = 10024, // updateMktDepthL2
    // ���Ź����¼�
    TWS_UPDATE_NEWS_BULLETIN = 10025, // updateNewsBulletin
    // �����˻��б��¼�
    TWS_MANAGED_ACCOUNTS = 10026, // managedAccounts
    // ����FA�����¼�
    TWS_RECEIVE_FA = 10027, // receiveFA
    // ��ʷ�����¼�
    TWS_HISTORICAL_DATA = 10028, // historicalData
    // ��ʷ���ݽ����¼�
    TWS_HISTORICAL_DATA_END = 10029, // historicalDataEnd
    // ɨ������¼�
    TWS_SCANNER_PARAMETERS = 10030, // scannerParameters
    // ɨ�������¼�
    TWS_SCANNER_DATA = 10031, // scannerData
    // ɨ�����ݽ����¼�
    TWS_SCANNER_DATA_END = 10032, // scannerDataEnd
    // ʵʱ����ͼ�����¼�
    TWS_REAL_TIME_BARS = 10033, // realtimeBar
    // ��ǰʱ���¼�
    TWS_CURRENT_TIME = 10034, // currentTime
    // �����������¼�
    TWS_FUNDAMENTAL_DATA = 10035, // fundamentalData
    // �¶���������֤�¼�
    TWS_DELTA_NEUTRAL_VALIDATION = 10036, // deltaNeutralValidation
    // �������ݽ����¼�
    TWS_TICK_SNAPSHOT_END = 10037, // tickSnapshotEnd
    // �г����������¼�
    TWS_MARKET_DATA_TYPE = 10038, // marketDataType
    // Ӷ�𱨸��¼�
    TWS_COMMISSION_REPORT = 10039, // commissionReport
    // �ֲָ����¼�
    TWS_POSITION = 10040, // position
    // �ֲָ��½����¼�
    TWS_POSITION_END = 10041, // positionEnd
    // �˻�ժҪ�����¼�
    TWS_ACCOUNT_SUMMARY = 10042, // accountSummary
    // �˻�ժҪ���½����¼�
    TWS_ACCOUNT_SUMMARY_END = 10043, // accountSummaryEnd
    // ��֤��ϢAPI�¼�
    TWS_VERIFY_MESSAGE_API = 10044, // verifyMessageAPI
    // ��֤����¼�
    TWS_VERIFY_COMPLETED = 10045, // verifyCompleted
    // ��ʾ���б��¼�
    TWS_DISPLAY_GROUP_LIST = 10046, // displayGroupList
    // ��ʾ������¼�
    TWS_DISPLAY_GROUP_UPDATED = 10047, // displayGroupUpdated
    // ��֤����Ȩ��ϢAPI�¼�
    TWS_VERIFY_AND_AUTH_MESSAGE_API = 10048, // verifyAndAuthMessageAPI
    // ��֤����Ȩ����¼�
    TWS_VERIFY_AND_AUTH_COMPLETED = 10049, // verifyAndAuthCompleted
    // ����ȷ���¼�
    TWS_CONNECT_ACK = 10050, // connectAck
    // ���˻��ֲָ����¼�
    TWS_POSITION_MULTI = 10051, // positionMulti
    // ���˻��ֲָ��½����¼�
    TWS_POSITION_MULTI_END = 10052, // positionMultiEnd
    // ���˻������¼�
    TWS_ACCOUNT_UPDATE_MULTI = 10053, // accountUpdateMulti
    // ���˻����½����¼�
    TWS_ACCOUNT_UPDATE_MULTI_END = 10054, // accountUpdateMultiEnd
    // ֤ȯ�����ѡ�����¼�
    TWS_SECURITY_DEFINITION_OPTIONAL_PARAMETER = 10055, // securityDefinitionOptionalParameter
    // ֤ȯ�����ѡ���������¼�
    TWS_SECURITY_DEFINITION_OPTIONAL_PARAMETER_END = 10056, // securityDefinitionOptionalParameterEnd
    // ����Ԫ�㼶�¼�
    TWS_SOFT_DOLLAR_TIERS = 10057, // softDollarTiers
    // ��������¼�
    TWS_FAMILY_CODES = 10058, // familyCodes
    // ���������¼�
    TWS_SYMBOL_SAMPLES = 10059, // symbolSamples
    // �г���Ƚ������¼�
    TWS_MKT_DEPTH_EXCHANGES = 10060, // mktDepthExchanges
    // �г����������¼�
    TWS_TICK_NEWS = 10061, // tickNews
    // ��������¼�
    TWS_SMART_COMPONENTS = 10062, // smartComponents
    // �г�������������¼�
    TWS_TICK_REQ_PARAMS = 10063, // tickReqParams
    // �����ṩ���б��¼�
    TWS_NEWS_PROVIDERS = 10064, // newsProviders
    // ���������¼�
    TWS_NEWS_ARTICLE = 10065, // newsArticle
    // ��ʷ�����¼�
    TWS_HISTORICAL_NEWS = 10066, // historicalNews
    // ��ʷ���Ž����¼�
    TWS_HISTORICAL_NEWS_END = 10067, // historicalNewsEnd
    // ͷ��ʱ����¼�
    TWS_HEAD_TIMESTAMP = 10068, // headTimestamp
    // ֱ��ͼ�����¼�
    TWS_HISTOGRAM_DATA = 10069, // histogramData
    // ��ʷ���ݸ����¼�
    TWS_HISTORICAL_DATA_UPDATE = 10070, // historicalDataUpdate
    // �ض����г����������¼�
    TWS_REROUTE_MKT_DATA_REQ = 10071, // rerouteMktDataReq
    // �ض����г���������¼�
    TWS_REROUTE_MKT_DEPTH_REQ = 10072, // rerouteMktDepthReq
    // �г������¼�
    TWS_MARKET_RULE = 10073, // marketRule
    // PnL�����¼�
    TWS_PNL = 10074, // pnl
    // ��һPnL�����¼�
    TWS_PNL_SINGLE = 10075, // pnlSingle
    // ��ʷTick�����¼�
    TWS_HISTORICAL_TICKS = 10076, // historicalTicks
    // ��ʷBidAsk Tick�����¼�
    TWS_HISTORICAL_TICKS_BID_ASK = 10077,
    // ��ʷBidAsk Tick�����¼�
    TWS_HISTORICAL_TICKS_BID_ASK = 10078, // historicalTicksBidAsk
    // ��ʷLast Tick�����¼�
    TWS_HISTORICAL_TICKS_LAST = 10079, // historicalTicksLast
    // Tick by Tick ȫ����������¼�
    TWS_TICK_BY_TICK_ALL_LAST = 10080, // tickByTickAllLast
    // Tick by Tick ���������¼�
    TWS_TICK_BY_TICK_BID_ASK = 10081, // tickByTickBidAsk
    // Tick by Tick �е������¼�
    TWS_TICK_BY_TICK_MID_POINT = 10082, // tickByTickMidPoint
    // �������¼�
    TWS_ORDER_BOUND = 10083, // orderBound
    // ��ɶ����¼�
    TWS_COMPLETED_ORDER = 10084, // completedOrder
    // ��ɶ��������¼�
    TWS_COMPLETED_ORDERS_END = 10085, // completedOrdersEnd
    // �滻FA�����¼�
    TWS_REPLACE_FA_END = 10086, // replaceFAEnd
    // WS������Ԫ�����¼�
    TWS_WSH_METADATA = 10087, // wshMetaData
    // WS���¼������¼�
    TWS_WSH_EVENT_DATA = 10088, // wshEventData
    // ��ʷʱ����¼�
    TWS_HISTORICAL_SCHEDULE = 10089, // historicalSchedule
    // �û���Ϣ�¼�
    TWS_USER_INFO = 10090 // userInfo
};
