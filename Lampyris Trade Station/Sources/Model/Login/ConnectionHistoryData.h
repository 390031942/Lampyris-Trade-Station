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
	typedef const IBGatewayHistoryConnectionInfo& ReadOnlyConnectionInfo;
	typedef std::vector<IBGatewayHistoryConnectionInfo> ConnectionInfoList;
	LAMPYRIS_DECLARE_SERILIZATION(IBGatewayHistoryConnectionDataObject);
public:
	void                    clearAllHistory() { m_historyInfoList.clear();}
	void                    setSaveIP(bool value) { m_saveIP = value; }
	bool                    getSaveIP() const { return m_saveIP; }
	void                    setAutoConnect(bool value) { m_autoConnect = value; }
	bool                    getAutoConnect() const { return m_autoConnect; }

	/* 
	 * 当IB网关/TWS连接成功后，将存储 最近连接的IBGatewayHistoryConnectionInfo
	*/
	void                    storage(const IBGatewayHistoryConnectionInfo connection);

	/* 
	 * 取得序列化存储的IBGatewayHistoryConnectionInfo
	 * 参数{index}:m_historyInfoList中的索引，如果index为-1，则取m_defaultIndex
	*/
	ReadOnlyConnectionInfo  getConnectionInfo(int index = -1) const;
private:	           
	int                     m_defaultIndex = -1; // 启动程序时，m_historyInfoList[m_defaultIndex]的值将作为默认值
	bool                    m_saveIP;
	bool                    m_autoConnect;
	ConnectionInfoList      m_historyInfoList;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(IBGatewayHistoryConnectionInfo) {
	LAMPYRIS_SERIALIZATION_FIELD(ip);
	LAMPYRIS_SERIALIZATION_FIELD(port);
	LAMPYRIS_SERIALIZATION_FIELD(clientId);
}
LAMPYRIS_SERIALIZATION_IMPL_END

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(IBGatewayHistoryConnectionDataObject)
{
	LAMPYRIS_SERIALIZATION_FIELD(m_defaultIndex);
	LAMPYRIS_SERIALIZATION_FIELD(m_saveIP);
	LAMPYRIS_SERIALIZATION_FIELD(m_autoConnect);
	LAMPYRIS_SERIALIZATION_FIELD(m_historyInfoList);
}
LAMPYRIS_SERIALIZATION_IMPL_END

#ifndef IBGatewayHistoryConnection
 #define IBGatewayHistoryConnection IBGatewayHistoryConnectionDataObject::getInstance()
#endif // !IBGatewayHistoryConnection