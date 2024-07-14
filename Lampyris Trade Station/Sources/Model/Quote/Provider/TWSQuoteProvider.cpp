/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "TWSQuoteProvider.h"
#include <Utility/DecimalUtil.h>

// TWS Include(s)
#include <TWS/ScannerSubscription.h>

Detailed::TWSQuoteProvider::TWSQuoteProvider() {
}

Detailed::TWSQuoteProvider::~TWSQuoteProvider() {

}

void Detailed::TWSQuoteProvider::subscribeQuoteUpdate(QuoteBaseDataPtr quoteData) {
	if (quoteData == nullptr)
		return;

	const QString& code = quoteData->infoData()->getCode();
	if (quoteData->getTickerId())
		return;
	
	int tickerId = m_tickerIdAutoIncrement++;
	quoteData->setTickerId(tickerId);

	TWSQuote->reqMktData(tickerId, quoteData->toContract(), "TRADES", false, false, TagValueListSPtr());
	m_tickerId2DataMap[tickerId] = quoteData;
}

void Detailed::TWSQuoteProvider::cancelSubscribeQuoteUpdate(QuoteBaseDataPtr quoteData) {
	if (quoteData == nullptr)
		return;

	const QString& code = quoteData->infoData()->getCode();
	int tickerId = quoteData->getTickerId();

	if (!m_tickerId2DataMap.contains(tickerId))
		return;

	TWSQuote->cancelMktData(tickerId);
	m_tickerId2DataMap.erase(tickerId);
}

void Detailed::TWSQuoteProvider::subscribeTickByTick(QuoteBaseDataPtr quoteData) {
	if (quoteData == nullptr)
		return;

	const QString& code = quoteData->infoData()->getCode();
	if (quoteData->getTickerId())
		return;

	int tickerId = m_tickerIdAutoIncrement++;

	TWSQuote->reqTickByTickData(tickerId, quoteData->toContract(), "LAST", 20 ,true);
	m_tickerId2DataMap[tickerId] = quoteData;
}

void Detailed::TWSQuoteProvider::cancelSubscribeTickByTick(QuoteBaseDataPtr quoteData) {
	if (quoteData == nullptr)
		return;

	const QString& code = quoteData->infoData()->getCode();
	int tickerId = quoteData->getTickerId();
	if (!m_tickerId2DataMap.contains(tickerId))
		return;

	TWSQuote->cancelTickByTickData(tickerId);
	m_tickerId2DataMap.erase(tickerId);
}

void Detailed::TWSQuoteProvider::bindEvent() {
	#define LAMPYRIS_CHECK_TICKER_ID(tickerId)\
		QuoteBaseDataPtr data = m_tickerId2DataMap[tickerId]; \
		if (!data) return;

	TWSEventBind(TWSEventType::onResTickPrice, [=](TickerId tickerId, TickType tickType, double price, const TickAttrib& attrib) {
		QuoteBaseDataPtr data = m_tickerId2DataMap[tickerId]; \
		if (!data) return;

		auto realTimeData = data->realTimeData();
		switch (tickType) {
		    case TickType::OPEN: /*开盘价*/
				realTimeData->setOpenPrice(price);
				break; 
		    case TickType::CLOSE: /*昨收*/
				realTimeData->setClosePrice(price);
				break;
			case TickType::HIGH: /*最高*/
				realTimeData->setHighPrice(price);
				break;
		    case TickType::LOW:  /*最低*/
				realTimeData->setLowPrice(price);
				break;
		    case TickType::ASK: /*买一价*/
				realTimeData->setAskPrice(1,price);
				break; 
			case TickType::BID: /*卖一价*/
				realTimeData->setBidPrice(1,price);
				break;
		}
	});

	TWSEventBind(TWSEventType::onResTickSize, [=](TickerId tickerId, TickType tickType, Decimal size) {
		QuoteBaseDataPtr data = m_tickerId2DataMap[tickerId]; \
			if (!data) return;

		double sizeF = DecimalUtil::toDouble(size);
		auto realTimeData = data->realTimeData();
		switch (tickType) {
		case TickType::VOLUME:  /*成交量*/
			realTimeData->setVolume(sizeF);
			break;
		case TickType::ASK_SIZE: /*买一量*/
			realTimeData->setAskSize(1, sizeF);
			break;
		case TickType::BID_SIZE:  /*卖一量*/
			realTimeData->setBidSize(1, sizeF);
			break;
		case TickType::TRADE_RATE: /*分钟成交笔数*/
			realTimeData->setOneMinuteTradeCount(sizeF);
			break;
		case TickType::TRADE_COUNT: /*成交笔数*/
			realTimeData->setTradeCount(sizeF);
			break;
		}
	});

	TWSEventBind(TWSEventType::onResTickString, [=](TickerId tickerId, TickType tickType, const std::string& value) {
		QuoteBaseDataPtr data = m_tickerId2DataMap[tickerId]; \
			if (!data) return;

		auto realTimeData = data->realTimeData();
		switch (tickType) {
		case TickType::LAST_TIMESTAMP: /*最后一笔成交时间*/
			realTimeData->setTimestmap(std::stol(value));
			break;
		case TickType::SHORTABLE_SHARES: /*可沽数量*/
			realTimeData->setShortableShares(std::stol(value));
			break;
		case TickType::RT_VOLUME: /*包含最后一笔交易的价格、规模和时间，以及当天的总交易量、交易量加权平均价格（VWAP）*/
			std::string numberStr;
			double number;

			// 使用istringstream来解析字符串,读取直到第五个分号
			std::istringstream iss(value);
			std::string token;

			for (int i = 0; i < 4; ++i) {
				std::getline(iss, token, ';');
			}

			// 读取第五个分号后的部分
			std::getline(iss, numberStr, ';');

			// 将字符串转换为double
			number = std::stod(numberStr);

			realTimeData->setVWAP(number);
			break;
		}
	});

	TWSEventBind(TWSEventType::onResTickGeneric, [=](TickerId tickerId, TickType tickType, double value) {
		QuoteBaseDataPtr data = m_tickerId2DataMap[tickerId]; \
			if (!data) return;

		auto realTimeData = data->realTimeData();
		switch (tickType) {
		case TickType::HALTED: /*最后一笔成交时间*/
			realTimeData->setHalted(value == 1 || value == 2);
			break;
		}
	});

	TWSEventBind(TWSEventType::onResTickByTickAllLast, [=](int reqId, int tickType, time_t time, double price, Decimal size, 
		                                                   const TickAttribLast& tickAttribLast, const std::string& exchange, 
		                                                   const std::string& specialConditions) {
		LAMPYRIS_CHECK_TICKER_ID(reqId);
		data->realTimeData()->recordTickByTick(time,price,DecimalUtil::toSingle(size));
	});

	#undef LAMPYRIS_CHECK_TICKER_ID
}