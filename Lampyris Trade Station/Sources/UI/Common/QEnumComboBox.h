/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <QComboBox>
#include <QStringList>

class QEnumComboBox : public QComboBox {
    Q_OBJECT
public:
               QEnumComboBox(QWidget* parent = nullptr);
    void       setEnum(const QString& enumName);
    void       setCurrentIndex(const QString& valueName);
    inline int selectedValue() const 
    { return currentData().toInt(); }
private:
    std::unordered_map<QString, int> m_enumDataMap;
};