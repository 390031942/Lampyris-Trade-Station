/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "EastMoneyQuoteProvider.h"
#include <Base/LogManager.h>

EastMoneyQuoteProvider::EastMoneyQuoteProvider() {
	m_httpRequestMgr.bind(ReqType::IndexBriefQuote, "http://42.push2.eastmoney.com/api/qt/clist/get",
		/** handler*/ [=](const QByteArray& bytes) {
			auto jsonDoc = QJsonDocument::fromJson(bytes);
			auto data = jsonDoc["data"];
			if (!data.isNull() && data.isObject()) {
				auto diff = data["diff"];
				if (diff.isArray()) {
					auto arr = diff.toArray();
					for (int i = 0; i < arr.size(); i++) {
						auto element = arr[i].toObject();

						// f2 = price,f3 = percentage,f4 = change,f12 = code,f14 = name
						float price = element["f2"].toDouble();
						float percentage = element["f3"].toDouble();
						float change = element["f4"].toDouble();
						QString code = element["f12"].toString();
						QString name = element["f14"].toString();

						IndexBriefQuoteData* pData = nullptr;
						if (m_indexBriefQuoteDataMap.contains(code)) {
							pData = &(m_indexBriefQuoteDataMap[code]);
						}
						else {
							pData = &(m_indexBriefQuoteDataMap[code] = IndexBriefQuoteData{0});
							pData->code = code;
							pData->name = name;
						}

						pData->price = price;
						pData->change = change;
						pData->percentage = percentage;
					}

					this->IIndexBriefQuoteProvider::m_isReady = true;
					return;
				}
			}
			Logger->logError(QString("Failed to parse json string, reqType = ReqType::IndexBriefQuote"));
		},
		/** error */ [=](const QString& error) {
			Logger->logError(QString("Failed to receive response, reason = \"%1\", reqType = ReqType::IndexBriefQuote").arg(error));
		}
	);
}

EastMoneyQuoteProvider::~EastMoneyQuoteProvider() {
}

void EastMoneyQuoteProvider::tick() {
	// 创建查询参数对象
	QUrlQuery query;

	// 添加查询参数
	query.addQueryItem("po", "1");
	query.addQueryItem("pz", "50");
	query.addQueryItem("pn", "1");
	query.addQueryItem("np", "1");
	query.addQueryItem("fltt", "2");
	query.addQueryItem("invt", "2");
	// query.addQueryItem("fs", "i:1.000001,i:0.399001,i:100.HSI,i:100.NDX");
	query.addQueryItem("fs", "i:100.NDX,i:100.DJIA,i:100.SPX");
	query.addQueryItem("fields", "f2,f3,f4,f12,f14");

	this->m_httpRequestMgr.get(ReqType::IndexBriefQuote,query);
}

EastMoneyQuoteProvider::ROIndexBriefQuoteData EastMoneyQuoteProvider::queryIndexBriefQuote(const QString& code) {
	return m_indexBriefQuoteDataMap[code];
}