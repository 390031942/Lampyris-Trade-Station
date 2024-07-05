/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

namespace TWSApiAbilities {
	/*
	 * 最大订阅的Scanner数量 
	*/
	static const int MAX_SCANNER_SUBSCRIBE_COUNT = 10;

	/*
	 * 最大Scanner返回数量 
	*/
	static const int MAX_SCANNER_RESULT_COUNT = 50;

	/*
	 * 最大单次获取历史tick的数量
	*/
	static const int MAX_HISTORICAL_TICK_ACOUNT = 1000;

	/*
	 * 最大逐笔订阅数量
	*/
	static const int MAX_TICK_BY_TICK_SUBSCRIBE_COUNT = 5;
}