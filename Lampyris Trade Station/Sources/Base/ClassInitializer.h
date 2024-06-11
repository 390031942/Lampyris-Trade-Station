/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#define LTS_DECLARE_CLASS_INITIALIZE(clsName) public: \
    static int __hiddenInteger; \
    static int StaticInitialize();

#define LTS_DECLARE_CLASS_BEGIN(clsName) \
	int clsName::__hiddenInteger = clsName::StaticInitialize(); \ 
	int clsName::StaticInitialize() {

#define LTS_DECLARE_CLASS_END(clsName) return 1; }