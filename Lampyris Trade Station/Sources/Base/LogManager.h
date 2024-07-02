/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "Singleton.h"

#ifndef Logger
 #define Logger LogManager::getInstance()
#endif // !Logger

class LogManager :public Singleton<LogManager> {
public:
	template<typename ...Args>
	void logMessageReceived(Args&&... args) {

	}

	void logInfo(const QString& info) {

	}

	void logWarning(const QString& warning) {

	}

	void logError(const QString& error) {

	}
private:
	template<typename ...Args>
	QString buildMessageLogString (Args&&... args) {

	}
};