/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "TWSMessageWrapper.h"
#include "TWSEventDispatcher.h"

// TWS Include(s)
#include <TWS/Contract.h>

void TWSMessageWrapper::tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib) {
	Logger->logMessageReceived("tickPrice", tickerId, field, price, attrib);
	emit TWSEventDispatcher->onResTickPrice(tickerId, field, price, attrib);
}

void TWSMessageWrapper::tickSize(TickerId tickerId, TickType field, Decimal size) {
	Logger->logMessageReceived("tickSize", tickerId, field, size);
	emit TWSEventDispatcher->onResTickSize(tickerId, field, size);
}

void TWSMessageWrapper::tickOptionComputation(TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {
	Logger->logMessageReceived("tickOptionComputation", tickerId, tickType, tickAttrib, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
	emit TWSEventDispatcher->onResTickOptionComputation(tickerId, tickType, tickAttrib, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
}

void TWSMessageWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value) {
	Logger->logMessageReceived("tickGeneric", tickerId, tickType, value);
	emit TWSEventDispatcher->onResTickGeneric(tickerId, tickType, value);
}

void TWSMessageWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value) {
	Logger->logMessageReceived("tickString", tickerId, tickType, value);
	emit TWSEventDispatcher->onResTickString(tickerId, tickType, value);
}

void TWSMessageWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) {
	Logger->logMessageReceived("tickEFP", tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
	emit TWSEventDispatcher->onResTickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
}

void TWSMessageWrapper::orderStatus(OrderId orderId, const std::string& status, Decimal filled, Decimal remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) {
	Logger->logMessageReceived("orderStatus", orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice);
	emit TWSEventDispatcher->onResOrderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice);
}

void TWSMessageWrapper::openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState) {
	Logger->logMessageReceived("openOrder", orderId, contract, order, orderState);
	emit TWSEventDispatcher->onResOpenOrder(orderId, contract, order, orderState);
}

void TWSMessageWrapper::openOrderEnd() {
	Logger->logMessageReceived("openOrderEnd");
	emit TWSEventDispatcher->onResOpenOrderEnd();
}

void TWSMessageWrapper::winError(const std::string& str, int lastError) {
	Logger->logMessageReceived("winError", str, lastError);
	emit TWSEventDispatcher->onResWinError(str, lastError);
}

void TWSMessageWrapper::connectionClosed() {
	Logger->logMessageReceived("connectionClosed");
	emit TWSEventDispatcher->onResConnectionClosed();
}

void TWSMessageWrapper::updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName) {
	Logger->logMessageReceived(key, val, currency, accountName);
	emit TWSEventDispatcher->onResUpdateAccountValue(key, val, currency, accountName);
}

void TWSMessageWrapper::updatePortfolio(const Contract& contract, Decimal position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName) {
	Logger->logMessageReceived(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
	emit TWSEventDispatcher->onResUpdatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
}

void TWSMessageWrapper::updateAccountTime(const std::string& timeStamp) {
	Logger->logMessageReceived(timeStamp);
	emit TWSEventDispatcher->onResUpdateAccountTime(timeStamp);
}

void TWSMessageWrapper::accountDownloadEnd(const std::string& accountName) {
	Logger->logMessageReceived(accountName);
	emit TWSEventDispatcher->onResAccountDownloadEnd(accountName);
}

void TWSMessageWrapper::nextValidId(OrderId orderId) {
	Logger->logMessageReceived(orderId);
	emit TWSEventDispatcher->onResNextValidId(orderId);
}

void TWSMessageWrapper::contractDetails(int reqId, const ContractDetails& contractDetails) {
	Logger->logMessageReceived(reqId, contractDetails);
	emit TWSEventDispatcher->onResContractDetails(reqId, contractDetails);
}

void TWSMessageWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails) {
	Logger->logMessageReceived(reqId, contractDetails);
	emit TWSEventDispatcher->onResBondContractDetails(reqId, contractDetails);
}

void TWSMessageWrapper::contractDetailsEnd(int reqId) {
	Logger->logMessageReceived(reqId);
	emit TWSEventDispatcher->onResContractDetailsEnd(reqId);
}

void TWSMessageWrapper::execDetails(int reqId, const Contract& contract, const Execution& execution) {
	Logger->logMessageReceived(reqId, contract, execution);
	emit TWSEventDispatcher->onResExecDetails(reqId, contract, execution);
}

void TWSMessageWrapper::execDetailsEnd(int reqId) {
	Logger->logMessageReceived(reqId);
	emit TWSEventDispatcher->onResExecDetailsEnd(reqId);
}

void TWSMessageWrapper::error(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson) {
	Logger->logMessageReceived(id, errorCode, errorString, advancedOrderRejectJson);
	emit TWSEventDispatcher->onResError(id, errorCode, errorString, advancedOrderRejectJson);
}

void TWSMessageWrapper::updateMktDepth(TickerId id, int position, int operation, int side, double price, Decimal size) {
	Logger->logMessageReceived(id, position, operation, side, price, size);
	emit TWSEventDispatcher->onResUpdateMktDepth(id, position, operation, side, price, size);
}

void TWSMessageWrapper::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, Decimal size, bool isSmartDepth) {
	Logger->logMessageReceived("updateMktDepthL2", id, position, marketMaker, operation, side, price, size, isSmartDepth);
	emit TWSEventDispatcher->onResUpdateMktDepthL2(id, position, marketMaker, operation, side, price, size, isSmartDepth);
}

void TWSMessageWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) {
	Logger->logMessageReceived("updateNewsBulletin", msgId, msgType, newsMessage, originExch);
	emit TWSEventDispatcher->onResUpdateNewsBulletin(msgId, msgType, newsMessage, originExch);
}

void TWSMessageWrapper::managedAccounts(const std::string& accountsList) {
	Logger->logMessageReceived("managedAccounts", accountsList);
	emit TWSEventDispatcher->onResManagedAccounts(accountsList);
}

void TWSMessageWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml) {
	Logger->logMessageReceived("receiveFA", pFaDataType, cxml);
	emit TWSEventDispatcher->onResReceiveFA(pFaDataType, cxml);
}

void TWSMessageWrapper::historicalData(TickerId reqId, const Bar& bar) {
	Logger->logMessageReceived("historicalData", reqId, bar);
	emit TWSEventDispatcher->onResHistoricalData(reqId, bar);
}

void TWSMessageWrapper::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr) {
	Logger->logMessageReceived("historicalDataEnd", reqId, startDateStr, endDateStr);
	emit TWSEventDispatcher->onResHistoricalDataEnd(reqId, startDateStr, endDateStr);
}

void TWSMessageWrapper::scannerParameters(const std::string& xml) {
	Logger->logMessageReceived("scannerParameters", xml);
	emit TWSEventDispatcher->onResScannerParameters(xml);
}

void TWSMessageWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr) {
	// Logger->logMessageReceived("scannerData", reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
	// emit TWSEventDispatcher->onResScannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);

	if (m_scannerReqId2DataListMap.contains(reqId)) {
		LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET(m_scannerReqId2DataListMap[reqId]);
	}

	m_scannerReqId2DataListMap[reqId].data.push_back(contractDetails.contract);
}

void TWSMessageWrapper::scannerDataEnd(int reqId) {
	auto& kepper = m_scannerReqId2DataListMap[reqId];
	kepper.ready = true;
	emit TWSEventDispatcher->onResScannerDataEnd(kepper.data);
}

void TWSMessageWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, Decimal volume, Decimal wap, int count) {
	Logger->logMessageReceived("realtimeBar", reqId, time, open, high, low, close, volume, wap, count);
	emit TWSEventDispatcher->onResRealtimeBar(reqId, time, open, high, low, close, volume, wap, count);
}

void TWSMessageWrapper::currentTime(long time) {
	Logger->logMessageReceived("currentTime", time);
	emit TWSEventDispatcher->onResCurrentTime(time);
}

void TWSMessageWrapper::fundamentalData(TickerId reqId, const std::string& data) {
	Logger->logMessageReceived("fundamentalData", reqId, data);
	emit TWSEventDispatcher->onResFundamentalData(reqId, data);
}

void TWSMessageWrapper::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) {
	Logger->logMessageReceived("deltaNeutralValidation", reqId, deltaNeutralContract);
	emit TWSEventDispatcher->onResDeltaNeutralValidation(reqId, deltaNeutralContract);
}

void TWSMessageWrapper::tickSnapshotEnd(int reqId) {
	Logger->logMessageReceived("tickSnapshotEnd", reqId);
	emit TWSEventDispatcher->onResTickSnapshotEnd(reqId);
}

void TWSMessageWrapper::marketDataType(TickerId reqId, int marketDataType) {
	Logger->logMessageReceived("marketDataType", reqId, marketDataType);
	emit TWSEventDispatcher->onResMarketDataType(reqId, marketDataType);
}

void TWSMessageWrapper::commissionReport(const CommissionReport& commissionReport) {
	Logger->logMessageReceived("commissionReport", commissionReport);
	emit TWSEventDispatcher->onResCommissionReport(commissionReport);
}

void TWSMessageWrapper::position(const std::string& account, const Contract& contract, Decimal position, double avgCost) {
	// Logger->logMessageReceived("position", account, contract, position, avgCost);
	// emit TWSEventDispatcher->onResPosition(account, contract, position, avgCost);

	LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET(m_positionDataKeeper);
	m_positionDataKeeper.data.push_back(PositionData{ contract,position,avgCost });
}

void TWSMessageWrapper::positionEnd() {
	Logger->logMessageReceived("positionEnd");
	emit TWSEventDispatcher->onResPositionEnd(m_positionDataKeeper.data);
}

void TWSMessageWrapper::accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& currency) {
	Logger->logMessageReceived("accountSummary", reqId, account, tag, value, currency);
	emit TWSEventDispatcher->onResAccountSummary(reqId, account, tag, value, currency);
}

void TWSMessageWrapper::accountSummaryEnd(int reqId) {
	Logger->logMessageReceived("accountSummaryEnd", reqId);
	emit TWSEventDispatcher->onResAccountSummaryEnd(reqId);
}

void TWSMessageWrapper::verifyMessageAPI(const std::string& apiData) {
	Logger->logMessageReceived("verifyMessageAPI", apiData);
	emit TWSEventDispatcher->onResVerifyMessageAPI(apiData);
}

void TWSMessageWrapper::verifyCompleted(bool isSuccessful, const std::string& errorText) {
	Logger->logMessageReceived("verifyCompleted", isSuccessful, errorText);
	emit TWSEventDispatcher->onResVerifyCompleted(isSuccessful, errorText);
}

void TWSMessageWrapper::displayGroupList(int reqId, const std::string& groups) {
	Logger->logMessageReceived("displayGroupList", reqId, groups);
	emit TWSEventDispatcher->onResDisplayGroupList(reqId, groups);
}

void TWSMessageWrapper::displayGroupUpdated(int reqId, const std::string& contractInfo) {
	Logger->logMessageReceived("displayGroupUpdated", reqId, contractInfo);
	emit TWSEventDispatcher->onResDisplayGroupUpdated(reqId, contractInfo);
}

void TWSMessageWrapper::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange) {
	Logger->logMessageReceived("verifyAndAuthMessageAPI", apiData, xyzChallange);
	emit TWSEventDispatcher->onResVerifyAndAuthMessageAPI(apiData, xyzChallange);
}

void TWSMessageWrapper::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText) {
	Logger->logMessageReceived("verifyAndAuthCompleted", isSuccessful, errorText);
	emit TWSEventDispatcher->onResVerifyAndAuthCompleted(isSuccessful, errorText);
}

void TWSMessageWrapper::connectAck() {
	Logger->logMessageReceived("connectAck");
	emit TWSEventDispatcher->onResConnectAck();
}

void TWSMessageWrapper::positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, Decimal pos, double avgCost) {
	Logger->logMessageReceived("positionMulti", reqId, account, modelCode, contract, pos, avgCost);
	emit TWSEventDispatcher->onResPositionMulti(reqId, account, modelCode, contract, pos, avgCost);
}

void TWSMessageWrapper::positionMultiEnd(int reqId) {
	Logger->logMessageReceived("positionMultiEnd", reqId);
	emit TWSEventDispatcher->onResPositionMultiEnd(reqId);
}

void TWSMessageWrapper::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) {
	Logger->logMessageReceived("accountUpdateMulti", reqId, account, modelCode, key, value, currency);
	emit TWSEventDispatcher->onResAccountUpdateMulti(reqId, account, modelCode, key, value, currency);
}

void TWSMessageWrapper::accountUpdateMultiEnd(int reqId) {
	Logger->logMessageReceived("accountUpdateMultiEnd", reqId);
	emit TWSEventDispatcher->onResAccountUpdateMultiEnd(reqId);
}

void TWSMessageWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) {
	Logger->logMessageReceived("securityDefinitionOptionalParameter", reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);
	emit TWSEventDispatcher->onResSecurityDefinitionOptionalParameter(reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);
}

void TWSMessageWrapper::securityDefinitionOptionalParameterEnd(int reqId) {
	Logger->logMessageReceived("securityDefinitionOptionalParameterEnd", reqId);
	emit TWSEventDispatcher->onResSecurityDefinitionOptionalParameterEnd(reqId);
}

void TWSMessageWrapper::softDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers) {
	Logger->logMessageReceived("softDollarTiers", reqId, tiers);
	emit TWSEventDispatcher->onResSoftDollarTiers(reqId, tiers);
}

void TWSMessageWrapper::familyCodes(const std::vector<FamilyCode>& familyCodes) {
	Logger->logMessageReceived("familyCodes", familyCodes);
	emit TWSEventDispatcher->onResFamilyCodes(familyCodes);
}

void TWSMessageWrapper::symbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions) {
	Logger->logMessageReceived("symbolSamples", reqId, contractDescriptions);
	emit TWSEventDispatcher->onResSymbolSamples(reqId, contractDescriptions);
}

void TWSMessageWrapper::mktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions) {
	Logger->logMessageReceived("mktDepthExchanges", depthMktDataDescriptions);
	emit TWSEventDispatcher->onResMktDepthExchanges(depthMktDataDescriptions);
}

void TWSMessageWrapper::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) {
	Logger->logMessageReceived("tickNews", tickerId, timeStamp, providerCode, articleId, headline, extraData);
	emit TWSEventDispatcher->onResTickNews(tickerId, timeStamp, providerCode, articleId, headline, extraData);
}

void TWSMessageWrapper::smartComponents(int reqId, const SmartComponentsMap& theMap) {
	Logger->logMessageReceived("smartComponents", reqId, theMap);
	emit TWSEventDispatcher->onResSmartComponents(reqId, theMap);
}

void TWSMessageWrapper::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) {
	Logger->logMessageReceived("tickReqParams", tickerId, minTick, bboExchange, snapshotPermissions);
	emit TWSEventDispatcher->onResTickReqParams(tickerId, minTick, bboExchange, snapshotPermissions);
}

void TWSMessageWrapper::newsProviders(const std::vector<NewsProvider>& newsProviders) {
	Logger->logMessageReceived("newsProviders", newsProviders);
	emit TWSEventDispatcher->onResNewsProviders(newsProviders);
}

void TWSMessageWrapper::newsArticle(int requestId, int articleType, const std::string& articleText) {
	Logger->logMessageReceived("newsArticle", requestId, articleType, articleText);
	emit TWSEventDispatcher->onResNewsArticle(requestId, articleType, articleText);
}

void TWSMessageWrapper::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) {
	Logger->logMessageReceived("historicalNews", requestId, time, providerCode, articleId, headline);
	emit TWSEventDispatcher->onResHistoricalNews(requestId, time, providerCode, articleId, headline);
}

void TWSMessageWrapper::historicalNewsEnd(int requestId, bool hasMore) {
	Logger->logMessageReceived("historicalNewsEnd", requestId, hasMore);
	emit TWSEventDispatcher->onResHistoricalNewsEnd(requestId, hasMore);
}

void TWSMessageWrapper::headTimestamp(int reqId, const std::string& headTimestamp) {
	Logger->logMessageReceived("headTimestamp", reqId, headTimestamp);
	emit TWSEventDispatcher->onResHeadTimestamp(reqId, headTimestamp);
}

void TWSMessageWrapper::histogramData(int reqId, const HistogramDataVector& data) {
	Logger->logMessageReceived("histogramData", reqId, data);
	emit TWSEventDispatcher->onResHistogramData(reqId, data);
}

void TWSMessageWrapper::historicalDataUpdate(TickerId reqId, const Bar& bar) {
	Logger->logMessageReceived("historicalDataUpdate", reqId, bar);
	emit TWSEventDispatcher->onResHistoricalDataUpdate(reqId, bar);
}

void TWSMessageWrapper::rerouteMktDataReq(int reqId, int conid, const std::string& exchange) {
	Logger->logMessageReceived("rerouteMktDataReq", reqId, conid, exchange);
	emit TWSEventDispatcher->onResRerouteMktDataReq(reqId, conid, exchange);
}

void TWSMessageWrapper::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) {
	Logger->logMessageReceived("rerouteMktDepthReq", reqId, conid, exchange);
	emit TWSEventDispatcher->onResRerouteMktDepthReq(reqId, conid, exchange);
}

void TWSMessageWrapper::marketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements) {
	Logger->logMessageReceived("marketRule", marketRuleId, priceIncrements);
	emit TWSEventDispatcher->onResMarketRule(marketRuleId, priceIncrements);
}

void TWSMessageWrapper::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) {
	Logger->logMessageReceived("pnl", reqId, dailyPnL, unrealizedPnL, realizedPnL);
	emit TWSEventDispatcher->onResPnl(reqId, dailyPnL, unrealizedPnL, realizedPnL);
}

void TWSMessageWrapper::pnlSingle(int reqId, Decimal pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) {
	Logger->logMessageReceived("pnlSingle", reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value);
	emit TWSEventDispatcher->onResPnlSingle(reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value);
}

void TWSMessageWrapper::historicalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicks", reqId, ticks, done);
	emit TWSEventDispatcher->onResHistoricalTicks(reqId, ticks, done);
}

void TWSMessageWrapper::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicksBidAsk", reqId, ticks, done);
	emit TWSEventDispatcher->onResHistoricalTicksBidAsk(reqId, ticks, done);
}

void TWSMessageWrapper::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done) {
	Logger->logMessageReceived("historicalTicksLast", reqId, ticks, done);
	emit TWSEventDispatcher->onResHistoricalTicksLast(reqId, ticks, done);
}

void TWSMessageWrapper::tickByTickAllLast(int reqId, int tickType, time_t time, double price, Decimal size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions) {
	Logger->logMessageReceived("tickByTickAllLast", reqId, tickType, time, price, size, tickAttribLast, exchange, specialConditions);
	emit TWSEventDispatcher->onResTickByTickAllLast(reqId, tickType, time, price, size, tickAttribLast, exchange, specialConditions);
}

void TWSMessageWrapper::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk) {
	Logger->logMessageReceived("tickByTickBidAsk", reqId, time, bidPrice, askPrice, bidSize, askSize, tickAttribBidAsk);
	emit TWSEventDispatcher->onResTickByTickBidAsk(reqId, time, bidPrice, askPrice, bidSize, askSize, tickAttribBidAsk);
}

void TWSMessageWrapper::tickByTickMidPoint(int reqId, time_t time, double midPoint) {
	Logger->logMessageReceived("tickByTickMidPoint", reqId, time, midPoint);
	emit TWSEventDispatcher->onResTickByTickMidPoint(reqId, time, midPoint);
}

void TWSMessageWrapper::orderBound(long long orderId, int apiClientId, int apiOrderId) {
	Logger->logMessageReceived("orderBound", orderId, apiClientId, apiOrderId);
	emit TWSEventDispatcher->onResOrderBound(orderId, apiClientId, apiOrderId);
}

void TWSMessageWrapper::completedOrder(const Contract& contract, const Order& order, const OrderState& orderState) {
	Logger->logMessageReceived("completedOrder", contract, order, orderState);
	emit TWSEventDispatcher->onResCompletedOrder(contract, order, orderState);
}

void TWSMessageWrapper::completedOrdersEnd() {
	Logger->logMessageReceived("completedOrdersEnd");
	emit TWSEventDispatcher->onResCompletedOrdersEnd();
}

void TWSMessageWrapper::replaceFAEnd(int reqId, const std::string& text) {
	Logger->logMessageReceived("replaceFAEnd", reqId, text);
	emit TWSEventDispatcher->onResReplaceFAEnd(reqId, text);
}

void TWSMessageWrapper::wshMetaData(int reqId, const std::string& dataJson) {
	Logger->logMessageReceived("wshMetaData", reqId, dataJson);
	emit TWSEventDispatcher->onResWshMetaData(reqId, dataJson);
}

void TWSMessageWrapper::wshEventData(int reqId, const std::string& dataJson) {
	Logger->logMessageReceived("wshEventData", reqId, dataJson);
	emit TWSEventDispatcher->onResWshEventData(reqId, dataJson);
}

void TWSMessageWrapper::historicalSchedule(int reqId, const std::string& startDateTime, const std::string& endDateTime, const std::string& timeZone, const std::vector<HistoricalSession>& sessions) {
	Logger->logMessageReceived("historicalSchedule", reqId, startDateTime, endDateTime, timeZone, sessions);
	emit TWSEventDispatcher->onResHistoricalSchedule(reqId, startDateTime, endDateTime, timeZone, sessions);
}

void TWSMessageWrapper::userInfo(int reqId, const std::string& whiteBrandingId) {
	Logger->logMessageReceived("userInfo", reqId, whiteBrandingId);
	emit TWSEventDispatcher->onResUserInfo(reqId, whiteBrandingId);
}
