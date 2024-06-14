/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <type_traits>
#include <concepts>

// QT Include(s)
#include <QObject>

template<class T>
class Singleton {
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};

template<class T>
class SingletonQObject:public QObject {
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};