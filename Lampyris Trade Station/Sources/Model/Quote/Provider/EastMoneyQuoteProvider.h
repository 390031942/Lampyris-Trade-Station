/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Interface/QuoteInterface/IIndexBriefQuoteProvider.h>
#include <Interface/QuoteInterface/ISnapshotQuoteListProvider.h>
#include <Network/HttpRequestManager.h>
#include <Base/GlobalEventManager.h>

// QT Include(s)
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Detailed {
class EastMoneyQuoteProvider:public Singleton<EastMoneyQuoteProvider> {
	typedef std::unordered_map<QString, IndexBriefQuoteData> IndexBriefQuoteDataMap;
	typedef std::vector<SnapshotQuoteData> SnapshotQuoteDataList;
	enum ReqType {
		IndexBriefQuote = 1,
		AllSnapShotQuoteList = 2,
	};
public:
	const IndexBriefQuoteData&  queryIndexBriefQuote(const QString& code);
	const SnapshotQuoteDataList getSnapshotQuoteList();
	// ticker(s)
	void                        onTickIndexBriefQuoteProvider();
	void                        onTickSnapShotQuoteListProvider();
							   
	                            EastMoneyQuoteProvider();
						       ~EastMoneyQuoteProvider();
private:				       
	HttpRequestManager          m_httpRequestMgr;
	IndexBriefQuoteDataMap      m_indexBriefQuoteDataMap;
	SnapshotQuoteDataList       m_snapshotQuoteDataList;
};						       
} // end of namespace 'Detailed'

class EastMoneyIndexBriefQuoteProvider :public IIndexBriefQuoteProvider {
public:
	EastMoneyIndexBriefQuoteProvider() {
		GlobalEventManager::getInstance()->addEventHandler(GlobalEventType::EasyMoneyIndexBriefQuoteReady, [this](void** param) {
			
		});
	}

	virtual inline const IndexBriefQuoteData& queryIndexBriefQuote(const QString& code) override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->queryIndexBriefQuote(code);
	}

	virtual inline void tick() override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->onTickIndexBriefQuoteProvider();
	}
};

class EastMoneySnapshotQuoteListProvider :public ISnapshotQuoteListProvider {
public:
	EastMoneySnapshotQuoteListProvider() {
		GlobalEventManager::getInstance()->addEventHandler(GlobalEventType::EastMoneySnapshotQuoteListReady, [this](void** param) {
			this->updateSnapshotQuoteList(Detailed::EastMoneyQuoteProvider::getInstance()->getSnapshotQuoteList());
		});
	}

	virtual inline void tick() override {
		return Detailed::EastMoneyQuoteProvider::getInstance()->onTickSnapShotQuoteListProvider();
	}
};