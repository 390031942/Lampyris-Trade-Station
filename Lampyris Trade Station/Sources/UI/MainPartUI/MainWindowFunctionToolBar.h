/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QToolButton>
#include <QScrollArea>
#include <QVBoxLayout>

class IndexBriefQuoteItem;

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