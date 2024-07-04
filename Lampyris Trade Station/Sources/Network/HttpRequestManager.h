/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Qt Include(s)
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>

typedef std::function<void(const QByteArray&)> ReplyCallback;
typedef std::optional<std::function<void(const QString&)>> ErrorCallback;

struct HttpRequestInfo {
	QString         url;
	QNetworkRequest request;
	ReplyCallback   callback;
	ErrorCallback   errorCallback;
};

class HttpRequestManager:public QObject {
	Q_OBJECT
public:
	void  bind(int reqType, QString url, ReplyCallback callback, ErrorCallback errorCallback = ErrorCallback());
	void  get(int reqType, const QUrlQuery& query = QUrlQuery());
	void  post(int reqType,const QString& content, const QUrlQuery& query = QUrlQuery());
	void  post(int reqType,const QByteArray& contentBytes, const QUrlQuery& query = QUrlQuery());

	      HttpRequestManager();
	     ~HttpRequestManager();
private:
	void  handleReply(QNetworkReply* reply);

	QNetworkAccessManager m_manager;
	std::unordered_map<int, HttpRequestInfo> m_reqType2RequestInfoMap;
	std::unordered_map<QNetworkReply*, int> m_reply2reqTypeMap;
};