/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MessageWrapper.h"

void MessageWrapper::tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib) {
	Logger->logMessageReceived("tickPrice", tickerId, field, price, attrib);
	emit EventDispatcher->onResTickPrice(tickerId, field, price, attrib);
}

void MessageWrapper::tickSize(TickerId tickerId, TickType field, Decimal size) {
	Logger->logMessageReceived("tickSize", tickerId, field, size);
	emit EventDispatcher->onResTickSize(tickerId, field, size);
}

void MessageWrapper::tickOptionComputation(TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {
	Logger->logMessageReceived("tickOptionComputation", tickerId, tickType, tickAttrib, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
	emit EventDispatcher->onResTickOptionComputation(tickerId, tickType, tickAttrib, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
}

void MessageWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value) {
	Logger->logMessageReceived("tickGeneric", tickerId, tickType, value);
	emit EventDispatcher->onResTickGeneric(tickerId, tickType, value);
}

void MessageWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value) {
	Logger->logMessageReceived("tickString", tickerId, tickType, value);
	emit EventDispatcher->onResTickString(tickerId, tickType, value);
}

void MessageWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) {
	Logger->logMessageReceived("tickEFP", tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
	emit EventDispatcher->onResTickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
}

void MessageWrapper::orderStatus(OrderId orderId, const std::string& status, Decimal filled, Decimal remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) {
	Logger->logMessageReceived("orderStatus", orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice);
	emit EventDispatcher->onResOrderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice);
}

void MessageWrapper::openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState) {
	Logger->logMessageReceived("openOrder", orderId, contract, order, orderState);
	emit EventDispatcher->onResOpenOrder(orderId, contract, order, orderState);
}

void MessageWrapper::openOrderEnd() {
	Logger->logMessageReceived("openOrderEnd");
	emit EventDispatcher->onResOpenOrderEnd();
}

void MessageWrapper::winError(const std::string& str, int lastError) {
	Logger->logMessageReceived("winError", str, lastError);
	emit EventDispatcher->onResWinError(str, lastError);
}

void MessageWrapper::connectionClosed() {
	Logger->logMessageReceived("connectionClosed");
	emit EventDispatcher->onResConnectionClosed();
}

void MessageWrapper::updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName) {
	Logger->logMessageReceived(key, val, currency, accountName);
	emit EventDispatcher->onResUpdateAccountValue(key, val, currency, accountName);
}

void MessageWrapper::updatePortfolio(const Contract& contract, Decimal position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName) {
	Logger->logMessageReceived(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
	emit EventDispatcher->onResUpdatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
}

void MessageWrapper::updateAccountTime(const std::string& timeStamp) {
	Logger->logMessageReceived(timeStamp);
	emit EventDispatcher->onResUpdateAccountTime(timeStamp);
}

void MessageWrapper::accountDownloadEnd(const std::string& accountName) {
	Logger->logMessageReceived(accountName);
	emit EventDispatcher->onResAccountDownloadEnd(accountName);
}

void MessageWrapper::nextValidId(OrderId orderId) {
	Logger->logMessageReceived(orderId);
	emit EventDispatcher->onResNextValidId(orderId);
}

void MessageWrapper::contractDetails(int reqId, const ContractDetails& contractDetails) {
	Logger->logMessageReceived(reqId, contractDetails);
	emit EventDispatcher->onResContractDetails(reqId, contractDetails);
}

void MessageWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails) {
	Logger->logMessageReceived(reqId, contractDetails);
	emit EventDispatcher->onResBondContractDetails(reqId, contractDetails);
}

void MessageWrapper::contractDetailsEnd(int reqId) {
	Logger->logMessageReceived(reqId);
	emit EventDispatcher->onResContractDetailsEnd(reqId);
}

void MessageWrapper::execDetails(int reqId, const Contract& contract, const Execution& execution) {
	Logger->logMessageReceived(reqId, contract, execution);
	emit EventDispatcher->onResExecDetails(reqId, contract, execution);
}

void MessageWrapper::execDetailsEnd(int reqId) {
	Logger->logMessageReceived(reqId);
	emit EventDispatcher->onResExecDetailsEnd(reqId);
}

void MessageWrapper::error(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson) {
	Logger->logMessageReceived(id, errorCode, errorString, advancedOrderRejectJson);
	emit EventDispatcher->onResError(id, errorCode, errorString, advancedOrderRejectJson);
}

void MessageWrapper::updateMktDepth(TickerId id, int position, int operation, int side, double price, Decimal size) {
	Logger->logMessageReceived(id, position, operation, side, price, size);
	emit EventDispatcher->onResUpdateMktDepth(id, position, operation, side, price, size);
}

void MessageWrapper::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, Decimal size, bool isSmartDepth) {
	Logger->logMessageReceived("updateMktDepthL2", id, position, marketMaker, operation, side, price, size, isSmartDepth);
	emit EventDispatcher->onResUpdateMktDepthL2(id, position, marketMaker, operation, side, price, size, isSmartDepth);
}

void MessageWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) {
	Logger->logMessageReceived("updateNewsBulletin", msgId, msgType, newsMessage, originExch);
	emit EventDispatcher->onResUpdateNewsBulletin(msgId, msgType, newsMessage, originExch);
}

void MessageWrapper::managedAccounts(const std::string& accountsList) {
	Logger->logMessageReceived("managedAccounts", accountsList);
	emit EventDispatcher->onResManagedAccounts(accountsList);
}

void MessageWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml) {
	Logger->logMessageReceived("receiveFA", pFaDataType, cxml);
	emit EventDispatcher->onResReceiveFA(pFaDataType, cxml);
}

void MessageWrapper::historicalData(TickerId reqId, const Bar& bar) {
	Logger->logMessageReceived("historicalData", reqId, bar);
	emit EventDispatcher->onResHistoricalData(reqId, bar);
}

void MessageWrapper::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr) {
	Logger->logMessageReceived("historicalDataEnd", reqId, startDateStr, endDateStr);
	emit EventDispatcher->onResHistoricalDataEnd(reqId, startDateStr, endDateStr);
}

void MessageWrapper::scannerParameters(const std::string& xml) {
	Logger->logMessageReceived("scannerParameters", xml);
	emit EventDispatcher->onResScannerParameters(xml);
}

void MessageWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr) {
	Logger->logMessageReceived("scannerData", reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
	emit EventDispatcher->onResScannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
}

void MessageWrapper::scannerDataEnd(int reqId) {
	Logger->logMessageReceived("scannerDataEnd", reqId);
	emit EventDispatcher->onResScannerDataEnd(reqId);
}

void MessageWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, Decimal volume, Decimal wap, int count) {
	Logger->logMessageReceived("realtimeBar", reqId, time, open, high, low, close, volume, wap, count);
	emit EventDispatcher->onResRealtimeBar(reqId, time, open, high, low, close, volume, wap, count);
}

void MessageWrapper::currentTime(long time) {
	Logger->logMessageReceived("currentTime", time);
	emit EventDispatcher->onResCurrentTime(time);
}

void MessageWrapper::fundamentalData(TickerId reqId, const std::string& data) {
	Logger->logMessageReceived("fundamentalData", reqId, data);
	emit EventDispatcher->onResFundamentalData(reqId, data);
}

void MessageWrapper::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) {
	Logger->logMessageReceived("deltaNeutralValidation", reqId, deltaNeutralContract);
	emit EventDispatcher->onResDeltaNeutralValidation(reqId, deltaNeutralContract);
}

void MessageWrapper::tickSnapshotEnd(int reqId) {
	Logger->logMessageReceived("tickSnapshotEnd", reqId);
	emit EventDispatcher->onResTickSnapshotEnd(reqId);
}

void MessageWrapper::marketDataType(TickerId reqId, int marketDataType) {
	Logger->logMessageReceived("marketDataType", reqId, marketDataType);
	emit EventDispatcher->onResMarketDataType(reqId, marketDataType);
}

void MessageWrapper::commissionReport(const CommissionReport& commissionReport) {
	Logger->logMessageReceived("commissionReport", commissionReport);
	emit EventDispatcher->onResCommissionReport(commissionReport);
}

void MessageWrapper::position(const std::string& account, const Contract& contract, Decimal position, double avgCost) {
	Logger->logMessageReceived("position", account, contract, position, avgCost);
	emit EventDispatcher->onResPosition(account, contract, position, avgCost);
}

void MessageWrapper::positionEnd() {
	Logger->logMessageReceived("positionEnd");
	emit EventDispatcher->onResPositionEnd();
}

void MessageWrapper::accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& currency) {
	Logger->logMessageReceived("accountSummary", reqId, account, tag, value, currency);
	emit EventDispatcher->onResAccountSummary(reqId, account, tag, value, currency);
}

void MessageWrapper::accountSummaryEnd(int reqId) {
	Logger->logMessageReceived("accountSummaryEnd", reqId);
	emit EventDispatcher->onResAccountSummaryEnd(reqId);
}

void MessageWrapper::verifyMessageAPI(const std::string& apiData) {
	Logger->logMessageReceived("verifyMessageAPI", apiData);
	emit EventDispatcher->onResVerifyMessageAPI(apiData);
}

void MessageWrapper::verifyCompleted(bool isSuccessful, const std::string& errorText) {
	Logger->logMessageReceived("verifyCompleted", isSuccessful, errorText);
	emit EventDispatcher->onResVerifyCompleted(isSuccessful, errorText);
}

void MessageWrapper::displayGroupList(int reqId, const std::string& groups) {
	Logger->logMessageReceived("displayGroupList", reqId, groups);
	emit EventDispatcher->onResDisplayGroupList(reqId, groups);
}

void MessageWrapper::displayGroupUpdated(int reqId, const std::string& contractInfo) {
	Logger->logMessageReceived("displayGroupUpdated", reqId, contractInfo);
	emit EventDispatcher->onResDisplayGroupUpdated(reqId, contractInfo);
}

void MessageWrapper::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange) {
	Logger->logMessageReceived("verifyAndAuthMessageAPI", apiData, xyzChallange);
	emit EventDispatcher->onResVerifyAndAuthMessageAPI(apiData, xyzChallange);
}

void MessageWrapper::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText) {
	Logger->logMessageReceived("verifyAndAuthCompleted", isSuccessful, errorText);
	emit EventDispatcher->onResVerifyAndAuthCompleted(isSuccessful, errorText);
}

void MessageWrapper::connectAck() {
	Logger->logMessageReceived("connectAck");
	emit EventDispatcher->onResConnectAck();
}

void MessageWrapper::positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, Decimal pos, double avgCost) {
	Logger->logMessageReceived("positionMulti", reqId, account, modelCode, contract, pos, avgCost);
	emit EventDispatcher->onResPositionMulti(reqId, account, modelCode, contract, pos, avgCost);
}

void MessageWrapper::positionMultiEnd(int reqId) {
	Logger->logMessageReceived("positionMultiEnd", reqId);
	emit EventDispatcher->onResPositionMultiEnd(reqId);
}

void MessageWrapper::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) {
	Logger->logMessageReceived("accountUpdateMulti", reqId, account, modelCode, key, value, currency);
	emit EventDispatcher->onResAccountUpdateMulti(reqId, account, modelCode, key, value, currency);
}

void MessageWrapper::accountUpdateMultiEnd(int reqId) {
	Logger->logMessageReceived("accountUpdateMultiEnd", reqId);
	emit EventDispatcher->onResAccountUpdateMultiEnd(reqId);
}

void MessageWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) {
	Logger->logMessageReceived("securityDefinitionOptionalParameter", reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);
	emit EventDispatcher->onResSecurityDefinitionOptionalParameter(reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);
}

void MessageWrapper::securityDefinitionOptionalParameterEnd(int reqId) {
	Logger->logMessageReceived("securityDefinitionOptionalParameterEnd", reqId);
	emit EventDispatcher->onResSecurityDefinitionOptionalParameterEnd(reqId);
}

void MessageWrapper::softDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers) {
	Logger->logMessageReceived("softDollarTiers", reqId, tiers);
	emit EventDispatcher->onResSoftDollarTiers(reqId, tiers);
}

void MessageWrapper::familyCodes(const std::vector<FamilyCode>& familyCodes) {
	Logger->logMessageReceived("familyCodes", familyCodes);
	emit EventDispatcher->onResFamilyCodes(familyCodes);
}

void MessageWrapper::symbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions) {
	Logger->logMessageReceived("symbolSamples", reqId, contractDescriptions);
	emit EventDispatcher->onResSymbolSamples(reqId, contractDescriptions);
}

void MessageWrapper::mktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions) {
	Logger->logMessageReceived("mktDepthExchanges", depthMktDataDescriptions);
	emit EventDispatcher->onResMktDepthExchanges(depthMktDataDescriptions);
}

void MessageWrapper::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) {
	Logger->logMessageReceived("tickNews", tickerId, timeStamp, providerCode, articleId, headline, extraData);
	emit EventDispatcher->onResTickNews(tickerId, timeStamp, providerCode, articleId, headline, extraData);
}

void MessageWrapper::smartComponents(int reqId, const SmartComponentsMap& theMap) {
	Logger->logMessageReceived("smartComponents", reqId, theMap);
	emit EventDispatcher->onResSmartComponents(reqId, theMap);
}

void MessageWrapper::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) {
	Logger->logMessageReceived("tickReqParams", tickerId, minTick, bboExchange, snapshotPermissions);
	emit EventDispatcher->onResTickReqParams(tickerId, minTick, bboExchange, snapshotPermissions);
}

void MessageWrapper::newsProviders(const std::vector<NewsProvider>& newsProviders) {
	Logger->logMessageReceived("newsProviders", newsProviders);
	emit EventDispatcher->onResNewsProviders(newsProviders);
}

void MessageWrapper::newsArticle(int requestId, int articleType, const std::string& articleText) {
	Logger->logMessageReceived("newsArticle", requestId, articleType, articleText);
	emit EventDispatcher->onResNewsArticle(requestId, articleType, articleText);
}

void MessageWrapper::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) {
	Logger->logMessageReceived("historicalNews", requestId, time, providerCode, articleId, headline);
	emit EventDispatcher->onResHistoricalNews(requestId, time, providerCode, articleId, headline);
}

void MessageWrapper::historicalNewsEnd(int requestId, bool hasMore) {
	Logger->logMessageReceived("historicalNewsEnd", requestId, hasMore);
	emit EventDispatcher->onResHistoricalNewsEnd(requestId, hasMore);
}

void MessageWrapper::headTimestamp(int reqId, const std::string& headTimestamp) {
	Logger->logMessageReceived("headTimestamp", reqId, headTimestamp);
	emit EventDispatcher->onResHeadTimestamp(reqId, headTimestamp);
}

void MessageWrapper::histogramData(int reqId, const HistogramDataVector& data) {
	Logger->logMessageReceived("histogramData", reqId, data);
	emit EventDispatcher->onResHistogramData(reqId, data);
}

void MessageWrapper::historicalDataUpdate(TickerId reqId, const Bar& bar) {
	Logger->logMessageReceived("historicalDataUpdate", reqId, bar);
	emit EventDispatcher->onResHistoricalDataUpdate(reqId, bar);
}

void MessageWrapper::rerouteMktDataReq(int reqId, int conid, const std::string& exchange) {
	Logger->logMessageReceived("rerouteMktDataReq", reqId, conid, exchange);
	emit EventDispatcher->onResRerouteMktDataReq(reqId, conid, exchange);
}

void MessageWrapper::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) {
	Logger->logMessageReceived("rerouteMktDepthReq", reqId, conid, exchange);
	emit EventDispatcher->onResRerouteMktDepthReq(reqId, conid, exchange);
}

void MessageWrapper::marketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements) {
	Logger->logMessageReceived("marketRule", marketRuleId, priceIncrements);
	emit EventDispatcher->onResMarketRule(marketRuleId, priceIncrements);
}

void MessageWrapper::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) {
	Logger->logMessageReceived("pnl", reqId, dailyPnL, unrealizedPnL, realizedPnL);
	emit EventDispatcher->onResPnl(reqId, dailyPnL, unrealizedPnL, realizedPnL);
}

void MessageWrapper::pnlSingle(int reqId, Decimal pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) {
	Logger->logMessageReceived("pnlSingle", reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value);
	emit EventDispatcher->onResPnlSingle(reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value);
}

void MessageWrapper::historicalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicks", reqId, ticks, done);
	emit EventDispatcher->onResHistoricalTicks(reqId, ticks, done);
}

void MessageWrapper::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicksBidAsk", reqId, ticks, done);
	emit EventDispatcher->onResHistoricalTicksBidAsk(reqId, ticks, done);
}

void MessageWrapper::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicksLast", reqId, ticks, done);
	emit EventDispatcher->onResHistoricalTicksLast(reqId, ticks, done);
}

void MessageWrapper::tickByTickAllLast(int reqId, int tickType, time_t time, double price, Decimal size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions) {
	Logger->logMessageReceived("tickByTickAllLast", reqId, tickType, time, price, size, tickAttribLast, exchange, specialConditions);
	emit EventDispatcher->onResTickByTickAllLast(reqId, tickType, time, price, size, tickAttribLast, exchange, specialConditions);
}

void MessageWrapper::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk) {
	Logger->logMessageReceived("tickByTickBidAsk", reqId, time, bidPrice, askPrice, bidSize, askSize, tickAttribBidAsk);
	emit EventDispatcher->onResTickByTickBidAsk(reqId, time, bidPrice, askPrice, bidSize, askSize, tickAttribBidAsk);
}

void MessageWrapper::tickByTickMidPoint(int reqId, time_t time, double midPoint) {
	Logger->logMessageReceived("tickByTickMidPoint", reqId, time, midPoint);
	emit EventDispatcher->onResTickByTickMidPoint(reqId, time, midPoint);
}

void MessageWrapper::orderBound(long long orderId, int apiClientId, int apiOrderId) {
	Logger->logMessageReceived("orderBound", orderId, apiClientId, apiOrderId);
	emit EventDispatcher->onResOrderBound(orderId, apiClientId, apiOrderId);
}

void MessageWrapper::completedOrder(const Contract& contract, const Order& order, const OrderState& orderState) {
	Logger->logMessageReceived("completedOrder", contract, order, orderState);
	emit EventDispatcher->onResCompletedOrder(contract, order, orderState);
}

void MessageWrapper::completedOrdersEnd() {
	Logger->logMessageReceived("completedOrdersEnd");
	emit EventDispatcher->onResCompletedOrdersEnd();
}

void MessageWrapper::replaceFAEnd(int reqId, const std::string& text) {
	Logger->logMessageReceived("replaceFAEnd", reqId, text);
	emit EventDispatcher->onResReplaceFAEnd(reqId, text);
}

void MessageWrapper::wshMetaData(int reqId, const std::string& dataJson) {
	Logger->logMessageReceived("wshMetaData", reqId, dataJson);
	emit EventDispatcher->onResWshMetaData(reqId, dataJson);
}

void MessageWrapper::wshEventData(int reqId, const std::string& dataJson) {
	Logger->logMessageReceived("wshEventData", reqId, dataJson);
	emit EventDispatcher->onResWshEventData(reqId, dataJson);
}

void MessageWrapper::historicalSchedule(int reqId, const std::string& startDateTime, const std::string& endDateTime, const std::string& timeZone, const std::vector<HistoricalSession>& sessions) {
	Logger->logMessageReceived("historicalSchedule", reqId, startDateTime, endDateTime, timeZone, sessions);
	emit EventDispatcher->onResHistoricalSchedule(reqId, startDateTime, endDateTime, timeZone, sessions);
}

void MessageWrapper::userInfo(int reqId, const std::string& whiteBrandingId) {
	Logger->logMessageReceived("userInfo", reqId, whiteBrandingId);
	emit EventDispatcher->onResUserInfo(reqId, whiteBrandingId);
}
