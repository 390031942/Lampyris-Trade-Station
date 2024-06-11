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
	/*
	 * 序列化方法
	*/
	virtual void serialize() = 0;

	/*
	 * 反序列化方法
	*/
	virtual void deserialize() = 0;

	/*
	 * 在反序列化完成后执行的方法
	*/
	virtual void postDeserialize() {}

	/*
	 * 序列化本地的存储文件名
	*/
	virtual QString getStorageFileName() = 0;
};