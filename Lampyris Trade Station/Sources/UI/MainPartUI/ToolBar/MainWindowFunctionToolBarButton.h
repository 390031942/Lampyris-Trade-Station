/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QToolButton>
#include <QScrollArea>
#include <QVBoxLayout>

class MainWindowFunctionToolBarButton : public QToolButton {
    Q_OBJECT
public:
    explicit MainWindowFunctionToolBarButton(QWidget* parent = nullptr);
    void     setSelected(bool selected);
protected:
    void     enterEvent(QEvent* event) override;
    void     leaveEvent(QEvent* event) override;
    void     paintEvent(QPaintEvent* event) override;
private:
    bool     m_isSelected;
};