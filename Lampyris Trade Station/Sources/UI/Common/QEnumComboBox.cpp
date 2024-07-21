/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QEnumComboBox.h"
#include <Base/EnumManager.h>

QEnumComboBox::QEnumComboBox(QWidget* parent) : QComboBox(parent) {}

void QEnumComboBox::setEnum(const QString& enumName) {
    this->clear();
    const auto& enumFields = EnumManager::getInstance()->getEnum(enumName);
    for (const auto& field : enumFields) {
        auto& fieldText = std::get<2>(field);
        auto& value     = std::get<1>(field);

        this->addItem(fieldText, value);
        this->m_enumDataMap[fieldText] = value;
    }
}

void QEnumComboBox::setCurrentIndex(const QString& valueName) {
    if (this->m_enumDataMap.contains(valueName)) {
        QComboBox::setCurrentIndex(this->m_enumDataMap[valueName]);
    }
}
