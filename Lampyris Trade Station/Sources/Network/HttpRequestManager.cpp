/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "HttpRequestManager.h"

void HttpRequestManager::bind(int reqType, QString url, ReplyCallback callback, ErrorCallback errorCallback) {
	if (!m_reqType2RequestInfoMap.contains(reqType)) {
		m_reqType2RequestInfoMap[reqType] = HttpRequestInfo{ url, QNetworkRequest(), callback, errorCallback };
	}
}

void HttpRequestManager::get(int reqType, const QUrlQuery& query) {
	if (m_reqType2RequestInfoMap.contains(reqType)) {
		const HttpRequestInfo& info = m_reqType2RequestInfoMap[reqType];
		QUrl url(info.url);
		url.setQuery(query);
		m_reply2reqTypeMap[m_manager.get(QNetworkRequest(url))] = reqType;
	}
}

void HttpRequestManager::post(int reqType, const QString& content, const QUrlQuery& query) {
	this->post(reqType, content.toUtf8(), query);
}

void HttpRequestManager::post(int reqType, const QByteArray& contentBytes, const QUrlQuery& query) {
	if (m_reqType2RequestInfoMap.contains(reqType)) {
		const HttpRequestInfo& info = m_reqType2RequestInfoMap[reqType];
		m_manager.post(info.request, contentBytes);
	}
}

HttpRequestManager::HttpRequestManager() {
	QObject::connect(&this->m_manager, &QNetworkAccessManager::finished, this, &HttpRequestManager::handleReply);
}

HttpRequestManager::~HttpRequestManager() {
	
}

void HttpRequestManager::handleReply(QNetworkReply* reply) {
	if (reply != nullptr) {
		if (m_reply2reqTypeMap.contains(reply)) {
			const HttpRequestInfo& info = m_reqType2RequestInfoMap[m_reply2reqTypeMap[reply]];
			if (reply->error() != QNetworkReply::NoError) {
				if (info.errorCallback.has_value()) {
					info.errorCallback.value()(reply->errorString());
				}
			}
			else {
				QByteArray bytes = reply->readAll();
				info.callback(bytes);
			}
		}
		this->m_reply2reqTypeMap.erase(reply);
		reply->deleteLater();
	}
}
