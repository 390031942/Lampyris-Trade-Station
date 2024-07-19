/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Core/Application.h>
#include <Interface/IStrategy.h>

/*
 * ��ǰ��һģ�� 
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
	// ģʽ
	PreMarketTopStrategyMode m_mode;

	// �̶�ʽ����-��������(%)
	float m_fixedModeTakeProfitPercentage = 10;

	// �̶�ʽ����-�س��������(%)
	float m_fixedModeFallAndBuyPercentage = -5;

	// �̶�ʽ����-�����λ(%)
	float m_fixedModePositionSize = 100;

	// ����ʽ����-�س��������{%,%,%...}
	QVector<float> m_stepModeFallAndBuyPercentage = {-2,-4,-8};

	// ����ʽ����-�����λ{%,%,%...}
	QVector<float> m_stepModeFallAndBuyPositionSize = { 20, 30, 50 };
};