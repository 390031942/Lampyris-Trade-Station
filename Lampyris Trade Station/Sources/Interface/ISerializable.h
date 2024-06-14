/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

/*
 * ��Ҫ�����л���������Ҫʵ�ֵĽӿڣ�
*/
class ISerializable {
public:
	virtual void serialize() = 0;
	virtual void deserialize() = 0;
	virtual void postDeserialize() {}
	virtual const std::string& getStorageFileName() = 0;
};