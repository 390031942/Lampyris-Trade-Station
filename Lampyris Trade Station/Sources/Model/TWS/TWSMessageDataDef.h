/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// TWS Include(s)
#include <TWS/Contract.h>

#ifndef LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET
#define LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET(dataKeeper) \
	if (dataKeeper.ready) { dataKeeper.ready = false; dataKeeper.data.clear(); }
#endif // !LAMPYRIS_TWS_MSG_DATA_KEEPER_RESET

template<typename T>
struct TWSDataListKepper {
	bool ready;
	std::vector<T> data;
};

struct PositionData {
	// �ֲֺ�Լ
	Contract  contract;
	// �ֲ�����
	Decimal   position;
	// ƽ���ɱ�
	double    avgCos;
};
