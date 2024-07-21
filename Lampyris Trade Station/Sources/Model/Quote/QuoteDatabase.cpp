/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QuoteDatabase.h"
#include <Core/Application.h>
#include <Core/TWSEventDispatcher.h>

QuoteDataReader QuoteDatabase::query(const QString& code, const QString& currency) {
	return QuoteDataReader(nullptr);
}

QuoteDatabase::SearchResultList QuoteDatabase::search(const QString& input) {
	SearchResultList result;
	searchNoAlloc(input, result);
	return result;
}

void QuoteDatabase::searchNoAlloc(const QString& input, SearchResultList& result) {
	result.clear();
	for (auto pair : m_dataMap) {
		auto info = pair.second->infoData();
		if (info->getCode().startsWith(input) || info->getName().contains(input)) {
			result.push_back(pair.second);
		}
	}
}

void QuoteDatabase::refreshStockList() {
	if (this->m_snapshotQuoteListProvider) {
		this->m_snapshotQuoteListProvider->tick();
	}
}

void QuoteDatabase::setSnapShotQuoteListProvider(ISnapshotQuoteListProvider* provider) {
	if (provider == nullptr || this->m_snapshotQuoteListProvider == provider)
		return;

	if (this->m_snapshotQuoteListProvider != nullptr) {
		this->m_snapshotQuoteListProvider->updateSnapshotQuoteList -= this->m_updateSnapShotQuoteListCallbackId;
	}
	this->m_snapshotQuoteListProvider = provider;

	this->m_updateSnapShotQuoteListCallbackId = (this->m_snapshotQuoteListProvider->updateSnapshotQuoteList
		+= [=](const std::vector<SnapshotQuoteData>& snapShotQuoteDataList) {
			for (auto& snapShot : snapShotQuoteDataList) {
				if (!m_dataMap.contains(snapShot.code)) {
					auto quoteData = m_dataMap[snapShot.code] = new QuoteBaseData();
					auto infoData = quoteData->infoData();

					infoData->setCode(snapShot.code);
					infoData->setName(snapShot.name);
				}

				auto quoteData = m_dataMap[snapShot.code];
				auto realTimeQuoteData = quoteData->realTimeData();
				realTimeQuoteData->setPrice(snapShot.price);
				realTimeQuoteData->setChange(snapShot.change);
				realTimeQuoteData->setChangePercentage(snapShot.percentage);
			}
	});
}

const IndexBriefQuoteData& QuoteDatabase::queryIndexBriefQuote(const QString& code) {
	return this->m_indexBriefQuoteProvider->queryIndexBriefQuote(code);
}

void QuoteDatabase::subscribeIndexBriefQuote(const std::vector<QString>& codeList) {
	m_subscribeIndexBriefQuoteCodeList = codeList;
}

void QuoteDatabase::setIndexBriefQuoteProvider(IIndexBriefQuoteProvider* provider) {
	this->m_indexBriefQuoteProvider = provider;
}

int QuoteDatabase::commitScannerSubscription(const ScannerSubscription& scannerSubscription) {
	int tickerId = this->m_scannerIdIncrement++;
	TWSQuote->reqScannerSubscription(tickerId,scannerSubscription,TagValueListSPtr(), TagValueListSPtr());

	return tickerId;
}

void QuoteDatabase::cancelScannerSubscription(int scannerId) {
	TWSQuote->cancelScannerSubscription(scannerId);
}

std::vector<Contract> QuoteDatabase::getScannerResult(int scannerId) {
	return m_scannerReqId2DataListMap[scannerId];
}

QuoteDatabase::QuoteDatabase() {
	Application::addTickFunc([=]() {
		this->tick();
	});

	TWSEventBind(TWSEventType::onResScannerDataEnd, [=](int scannerReqId,const std::vector<Contract>& result) {
		m_scannerReqId2DataListMap[scannerReqId] = result;
	});
}

void QuoteDatabase::tick() {
	long timeStmap = QDateTime::currentDateTime().toTime_t();
	if (m_indexBriefQuoteProvider->m_isReady) {
		onUpdatendexBriefQuote();
		m_indexBriefQuoteProvider->m_isReady = false;
	}
	else {
		if (timeStmap - m_indexBriefQuoteProvider->m_lastTickTimestmap > this->m_indexBriefQuoteTickIntervalMs) {
			m_indexBriefQuoteProvider->tick();
			m_indexBriefQuoteProvider->m_lastTickTimestmap = timeStmap;
		}
	}

}
