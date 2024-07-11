/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "StrategySettingItem.h"
#include <Model/Strategy/StrategyDescription.h>

StrategySettingItem::StrategySettingItem(QWidget* parent)
	:QWidget(parent) {
	this->m_ui.setupUi(this);
}

StrategySettingItem::~StrategySettingItem() {
}

void StrategySettingItem::setStrategyDescription(const StrategyDescription& info) {
}
