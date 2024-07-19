/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/Singleton.h>
#include <Const/GlobalEventType.h>

// STD Include(s)
#include <unordered_map>

typedef std::function<void(void**)> GlobalEventCallback;

class GlobalEventManager :public Singleton<GlobalEventManager> {
	struct GlobalEventData {
		int                 callbackId;
		GlobalEventCallback callback;
	};

	typedef std::unordered_map<GlobalEventType, std::vector<GlobalEventData>> EventMap;
public:
	int       addEventHandler(GlobalEventType type, GlobalEventCallback callback);
	void      removeEventHandler(GlobalEventType type,int callbackId);
	void      raiseEvent(GlobalEventType type, void* params[] = nullptr);
private:
	EventMap  m_eventMap;
	int       m_callbackIdAutoIncrement = 0;
};