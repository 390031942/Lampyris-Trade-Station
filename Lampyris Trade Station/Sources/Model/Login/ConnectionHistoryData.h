/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>

struct IBGatewayHistoryConnectionInfo {
	LAMPYRIS_DECLARE_SERILIZATION(IBGatewayHistoryConnectionInfo);
	QString ip;
	int     port;
	int     clientId;
};

class IBGatewayHistoryConnectionDataObject:public SerializableSingleton<IBGatewayHistoryConnectionDataObject> {
	LAMPYRIS_DECLARE_SERILIZATION(IBGatewayHistoryConnectionDataObject);
public:
	void clearAllHistory() {
		historyInfoList.clear();
	}
private:
	bool    saveIP;
	bool    autoConnect;

	// 保存了历史记录IP的列表
	std::vector<IBGatewayHistoryConnectionInfo> historyInfoList;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(IBGatewayHistoryConnectionInfo) {
	LAMPYRIS_SERIALIZATION_FIELD(ip);
	LAMPYRIS_SERIALIZATION_FIELD(port);
	LAMPYRIS_SERIALIZATION_FIELD(clientId);
}
LAMPYRIS_SERIALIZATION_IMPL_END

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(IBGatewayHistoryConnectionDataObject)
{
	LAMPYRIS_SERIALIZATION_FIELD(saveIP);
	LAMPYRIS_SERIALIZATION_FIELD(autoConnect);
	LAMPYRIS_SERIALIZATION_FIELD(historyInfoList);
}
LAMPYRIS_SERIALIZATION_IMPL_END