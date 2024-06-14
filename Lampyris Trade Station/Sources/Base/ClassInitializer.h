/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#define LAMPYRIS_DECLARE_CLASS_INITIALIZE(clsName) public: \
    static int __hiddenInteger; \
    static int __staticInitialize();

#define LAMPYRIS_DECLARE_CLASS_BEGIN(clsName) \
	int clsName::__hiddenInteger = clsName::__staticInitialize(); \ 
	int clsName::__staticInitialize() {

#define LAMPYRIS_DECLARE_CLASS_END(clsName) return 1; }