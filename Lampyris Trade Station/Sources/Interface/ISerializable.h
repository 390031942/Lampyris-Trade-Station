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
	/*
	 * ���л�����
	*/
	virtual void serialize() = 0;

	/*
	 * �����л�����
	*/
	virtual void deserialize() = 0;

	/*
	 * �ڷ����л���ɺ�ִ�еķ���
	*/
	virtual void postDeserialize() {}

	/*
	 * ���л����صĴ洢�ļ���
	*/
	virtual QString getStorageFileName() = 0;
};