/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>

class TimeDisplayItem : public QWidget {
    Q_OBJECT
public:
               TimeDisplayItem(QWidget* parent = nullptr);
              ~TimeDisplayItem();
protected:
    void       mousePressEvent(QMouseEvent* event) override;
private slots:
    void       updateTime();
    void       onPopupClosed();
private:
    QTimer*    m_timer;
    QLabel*    m_timeLabel;
    QWidget*   m_popupWidget;
    QCheckBox* m_checkBoxCN;
    QCheckBox* m_checkBoxUS;
    bool       m_isCNTime;
};