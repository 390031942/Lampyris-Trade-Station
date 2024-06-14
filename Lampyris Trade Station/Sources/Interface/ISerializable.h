/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

/*
 * 需要被序列化的类所需要实现的接口：
*/
class ISerializable {
public:
	virtual void serialize() = 0;
	virtual void deserialize() = 0;
	virtual void postDeserialize() {}
	virtual const std::string& getStorageFileName() = 0;
};