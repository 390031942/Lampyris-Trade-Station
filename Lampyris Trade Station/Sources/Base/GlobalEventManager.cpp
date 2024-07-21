/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "GlobalEventManager.h"

int GlobalEventManager::addEventHandler(GlobalEventType type, GlobalEventCallback callback) {
	if (callback == nullptr)
		return -1;
	GlobalEventData eventData;
	eventData.callbackId = ++this->m_callbackIdAutoIncrement;
	eventData.callback   = std::move(callback);
	this->m_eventMap[type].push_back(eventData);

	return eventData.callbackId;
}

void GlobalEventManager::removeEventHandler(GlobalEventType type, int callbackId) {
	if (callbackId <= 0) {
		return;
	}
	auto& list = this->m_eventMap[type];
	int index = -1;
	for (int i = 0; i < list.size(); i++) {
		if (list[i].callbackId == callbackId) {
			index = i; break;
		}
	}
	if (index >= 0) {
		list.erase(list.begin() + index);
	}
}

void GlobalEventManager::raiseEvent(GlobalEventType type, void* params[]) {
	auto& list = m_eventMap[type];
	for (GlobalEventData eventData : list) {
		eventData.callback(params);
	}
}
