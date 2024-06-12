/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// Boost Include(s)
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/access.hpp>

// QT Include(s)
#include <QString>

struct IBGatewayHistoryConnectionInfo {
	QString ip;
	int     port;
	int     clientId;
};

class IBGatewayHistoryConnectionDataObject {
public:
	// 序列化函数
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(saveIP);
		ar& BOOST_SERIALIZATION_NVP(autoConnect);
		ar& BOOST_SERIALIZATION_NVP(historyInfoList);
	}

	void saveHistory(QString ip,int port,int clientId) {
		for (int i = 0; i < historyInfoList.size(); i++) {
			if (historyInfoList[i].ip == ip) {
				break;
			}
		}

		historyInfoList.push_back(IBGatewayHistoryConnectionInfo{ip,port,clientId});
	}

	void clearAllHistory() {
		historyInfoList.clear();
	}
private:
	bool    saveIP;
	bool    autoConnect;

	// 保存了历史记录IP的列表
	std::vector<IBGatewayHistoryConnectionInfo> historyInfoList;
};