/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "EastMoneyQuoteProvider.h"
#include <Base/LogManager.h>

EastMoneyQuoteProvider::ROIndexBriefQuoteData EastMoneyQuoteProvider::queryIndexBriefQuote(const QString& code) const{

}

EastMoneyQuoteProvider::EastMoneyQuoteProvider() {
	m_httpRequestMgr.bind(ReqType::IndexBriefQuote, "http://42.push2.eastmoney.com/api/qt/clist/get",
		/** handler*/ [=](const QByteArray& bytes) {
			auto jsonDoc = QJsonDocument::fromJson(bytes);
			auto data = jsonDoc["data"];
			if (!data.isNull() && data.isObject()) {
				auto diff = data["diff"];
				if (diff.isArray()) {
					auto arr = diff.toArray();
					IndexBriefQuoteData tempData {0};

					for (int i = 0; i < arr.size(); i++) {
						auto element = arr[i].toObject();

						// f2 = price,f3 = percentage,f4 = change,f12 = code,f14 = name
						float price = element["f2"].toDouble();
						float percentage = element["f3"].toDouble();
						float change = element["f4"].toDouble();
						QString code = element["f12"].toString();
						QString name = element["f14"].toString();

						IndexBriefQuoteData* pData = &tempData;
						if (m_indexBriefQuoteDataMap.contains(code)) {
							pData = &(m_indexBriefQuoteDataMap[code]);
						}
						else {
							pData->code = code;
							pData->name = name;
						}

						pData->price = price;
						pData->change = change;
						pData->percentage = percentage;
					}
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
