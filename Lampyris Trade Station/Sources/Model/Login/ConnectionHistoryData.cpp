/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectionHistoryData.h"

void IBGatewayHistoryConnectionDataObject::storage(const IBGatewayHistoryConnectionInfo connection) {
	for (const IBGatewayHistoryConnectionInfo& info : m_historyInfoList) {
		if (info.ip == connection.ip && info.port == info.port) {
			return;
		}
	}
	m_historyInfoList.push_back(connection);
	m_defaultIndex = m_historyInfoList.size() - 1;
}

IBGatewayHistoryConnectionDataObject::ReadOnlyConnectionInfo IBGatewayHistoryConnectionDataObject::getConnectionInfo(int index) const {
	if (index == -1 && m_defaultIndex >= 0 && m_defaultIndex < m_historyInfoList.size()) {
		return m_historyInfoList[m_defaultIndex];
	}
	else if (index >= 0 && index < m_historyInfoList.size()) {
		return m_historyInfoList[index];
	}
	return IBGatewayHistoryConnectionInfo();
}
