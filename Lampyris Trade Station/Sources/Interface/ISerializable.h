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
	virtual void Serialize() = 0;

	/*
	 * �����л�����
	*/
	virtual void Deserialize() = 0;

	/*
	 * �ڷ����л���ɺ�ִ�еķ���
	*/
	virtual void PostDeserialize() {}

	/*
	 * ���л����صĴ洢�ļ���
	*/
	virtual QString GetStorageFileName() = 0;
};