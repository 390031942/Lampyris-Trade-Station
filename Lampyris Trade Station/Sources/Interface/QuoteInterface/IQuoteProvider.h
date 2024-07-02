/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// Project Include(s)
#include <Base/Delegate.h>

/*
 * ����ӿڻ��ࣺ
*/
class IQuoteProvider {
public:
	/* 
	 * QuoteProvider��tick����������ʱ���õĺ���
	*/
	Delegate<> updateQuoteCallback;
protected:
	/* 
	 * QuoteProvider��tick��ʱ����������ڼ������ �� ����ʵʱ�Լ���
	*/
	long m_lastTickTimestmap;

	/* 
	 * ��QuoteProvider��tick������׼����ϻ�����Ϊtrue��ʹ����Ϻ���������Ϊfalse
	*/
	bool m_isReady = false;

	/* 
	 * tick�������������������
	*/
	virtual void tick() = 0;

	friend class QuoteDatabase;
};