/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <type_traits>
#include <concepts>

template<class T>
class Singleton {
public:
	static T* GetInstance() {
		static T t;
		return &t;
	}
};