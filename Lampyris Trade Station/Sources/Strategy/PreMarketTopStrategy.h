/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Interface/IStrategy.h>

/*
 * 盘前龙一模型 
*/
class PreMarketTopStrategy:public IStrategy {
	Q_OBJECT
	LAMPYRIS_STRATEGY_DECLARE(PreMarketTopStrategy);

	Q_PROPERTY(float fixedModeTakeProfitPercentage MEMBER m_fixedModeTakeProfitPercentage);
	Q_PROPERTY(float fixedModeFallAndBuyPercentage MEMBER m_fixedModeFallAndBuyPercentage);
	Q_PROPERTY(float fixedModePositionSize MEMBER m_fixedModePositionSize);
	Q_PROPERTY(QVector<float> stepModeFallAndBuyPercentage MEMBER m_stepModeFallAndBuyPercentage);
	Q_PROPERTY(QVector<float> stepModeFallAndBuyPositionSize MEMBER m_stepModeFallAndBuyPositionSize);
	Q_PROPERTY(PreMarketTopStrategy::PreMarketTopStrategyMode mode MEMBER m_mode);

public:
	enum PreMarketTopStrategyMode {
		Fixed = 1,
		Step = 2,
	};
	Q_ENUM(PreMarketTopStrategyMode);

	bool executeCondition();
	bool tick();
private:
	// 模式
	PreMarketTopStrategyMode m_mode;

	// 固定式买入-获利比例(%)
	float m_fixedModeTakeProfitPercentage = 10;

	// 固定式买入-回撤买入比例(%)
	float m_fixedModeFallAndBuyPercentage = -5;

	// 固定式买入-买入仓位(%)
	float m_fixedModePositionSize = 100;

	// 阶梯式买入-回撤买入比例{%,%,%...}
	QVector<float> m_stepModeFallAndBuyPercentage = {-2,-4,-8};

	// 阶梯式买入-买入仓位{%,%,%...}
	QVector<float> m_stepModeFallAndBuyPositionSize = { 20, 30, 50 };
};