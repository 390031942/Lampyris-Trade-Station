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
	 * ��IB����/TWS���ӳɹ��󣬽��洢 ������ӵ�IBGatewayHistoryConnectionInfo
	*/
	void                    storage(const IBGatewayHistoryConnectionInfo connection);

	/* 
	 * ȡ�����л��洢��IBGatewayHistoryConnectionInfo
	 * ����{index}:m_historyInfoList�е����������indexΪ-1����ȡm_defaultIndex
	*/
	ReadOnlyConnectionInfo  getConnectionInfo(int index = -1) const;
private:	           
	int                     m_defaultIndex = -1; // ��������ʱ��m_historyInfoList[m_defaultIndex]��ֵ����ΪĬ��ֵ
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