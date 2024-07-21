/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/EnumManager.h>

enum TradeOrderType {
	Limit = 0,
	Market = 1,
};


/*
1.SMART-Smart Route:����·�ɽ���ϵͳ���ɶ�����������г���������ɣ�ּ���ṩ���ŵĽ��׼۸�,
2.AMEX-American Stock Exchange: ����֤ȯ����������ΪŦԼ֤ȯ��������һ���֡�
3.ARCA-Archipelago Exchange: Ⱥ������������ΪŦԼ֤ȯ��������һ���֡�
4.BATS-Bats Global Markets:ȫ���г����������ṩ��Ʊ���׷���������CBOE�ϲ���
5.BEX-Boston Stock Exchange: ��ʿ��֤ȯ����������Ϊ��˹��˵�һ���֡�
6.BYX-BYX Exchange: �ɲ�ʿ����Ȩ�������Ͳ�ʿ�ٹ�Ʊ�������ϲ����ɣ���Ϊ��˹��˵�һ���֡�
7.CBOE-Chicago Board Options Exchange: ֥�Ӹ���Ȩ���������ṩ��Ȩ���׷���
8.CHX-Chicago Stock Exchange: ֥�Ӹ��Ʊ���������ṩ��Ʊ���׷���
9.DRCTEDGE-Direct Edge:ֱ�ӱ�Ե���������ṩ��Ʊ���׷�����Ϊ��˹��˵�һ���֡�
10.EDGEA-EdgeA: ֱ�ӱ�Ե����������һ���֣����Ѳ�����˹��ˡ�
11,EDGX-EDGXExchanae;��Direct Edae��Ӫ����һ�����������ṩ��Ʊ���׷���,
12.IBKRTS-IBKR ATS: Interactive Brokers���������ϵͳ���ṩ��Ʊ����Ȩ���׷���
13.EX-Investors Exchange: Ͷ���߸���������һ����Ʊ�����������������������߶�������
14.ISE-International Securities Exchange: ����֤ȯ���������ṩ��Ȩ�͹�Ȩ����Ʒ���׷���
15.ISLAND-lsland ECN: �������ͨѶ���磬��һ�����ӽ���ƽ̨�����Ѳ�����˹���
16.LTSE-Long-Term Stock Exchange:���ڹ�Ʊ��������ּ�ڹ�������Ͷ�ʺ�͸���ȡ�
17.MEMX-Members Exchange:��Ա����������һ���³����Ľ�������ּ���ṩ���ͳɱ��Ľ��׷���
18.NVSE-National Stock Exchange: ����֤ȯ���������ṩ��Ʊ���׷���
19.NYSENAT-New York Stock Exchange National:ŦԼ֤ȯ���������Ұ棬��ŦԼ֤ȯ��������һ���֡�
20.PEARL-Pearl Exchange: ���齻�������ṩ��Ʊ���׷���
21.PHLX-Philadelphia Stock Exchange: �ѳǹ�Ʊ����������Ϊ��˹��˵�һ���֡�
22.PSX-Pacific Stock Exchange:̫ƽ���Ʊ���������ṩ��Ʊ����Ȩ���׷������Ѳ���ŦԼ֤ȯ��������
*/
enum TradeExchangeType {
	SMART = 0,
	AMEX = 1,
	ARCA = 2,
	BATS = 3,
	BEX = 4,
	BYX = 5,
	CBOE = 6,
	CHX = 7,
	DRCTEDGE = 8,
	EDGEA = 9,
	EDGX = 10,
	IBKRTS = 11,
	IEX = 12,
	ISE = 13,
	ISLAND = 14,
	LTSE = 15,
	MEMX = 16,
	NVSE = 17,
	NYSENAT = 18,
	PEARL = 19,
	PHLX = 20,
	PSX = 21,
};

enum TradeTIFType {
	DAY = 0, // ������Ч
	GTC = 1, // ȡ��ǰ��Ч
	GTD = 2, // ����ǰ��Ч
};

// �Ӷ�������
enum TradeSubOrderType {
	None = 0,
	TakeProfit = 1, // ֹӯ
	StopLoss = 2, // ֹ��
	Both = 3, // ֹӯ+ֹ��
};