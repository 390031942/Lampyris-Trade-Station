/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QObject>

template<class T>
class SingletonQObject:public QObject {
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};