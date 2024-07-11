/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class MainWindowFunctionToolBar : public QWidget {
    Q_OBJECT
public:
    explicit     MainWindowFunctionToolBar(QWidget* parent = nullptr);
private:
    void         clearSelection();
    QScrollArea* m_scrollArea;
    QWidget*     m_container;
    QVBoxLayout* m_containerLayout;
};