/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "TimeDisplayItem.h"
#include <Base/Localization.h>

// QT Include(s)
#include <QVBoxLayout>
#include <QDateTime>
#include <QMouseEvent>

TimeDisplayItem::TimeDisplayItem(QWidget* parent)
    : QWidget(parent)
    , m_timer(new QTimer(this))
    , m_timeLabel(new QLabel(this))
    , m_popupWidget(new QWidget(this))
    , m_checkBoxCN(new QCheckBox(Localization->get("TimeDisplayItem_1"), m_popupWidget))
    , m_checkBoxUS(new QCheckBox(Localization->get("TimeDisplayItem_2"), m_popupWidget))
    , m_isCNTime(true) {
    // 设置TimeDisplayItem布局
    m_timeLabel->setAlignment(Qt::AlignCenter);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_timeLabel);
    setLayout(mainLayout);

    // 设置定时器
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &TimeDisplayItem::updateTime);
    m_timer->start();

    // 设置弹窗布局
    QVBoxLayout* layout = new QVBoxLayout(m_popupWidget);
    layout->addWidget(m_checkBoxCN);
    layout->addWidget(m_checkBoxUS);
    m_popupWidget->setLayout(layout);
    m_popupWidget->setWindowFlags(Qt::Popup);
    m_popupWidget->hide();

    // 初始化默认值
    m_checkBoxCN->setChecked(true);

    connect(m_checkBoxCN, &QCheckBox::stateChanged, [this](int state) {
        if (state == Qt::Checked) {
            m_checkBoxUS->setChecked(false);
            m_isCNTime = true;
        }
        this->updateTime();
    });

    connect(m_checkBoxUS, &QCheckBox::stateChanged, [this](int state) {
        if (state == Qt::Checked) {
            m_checkBoxCN->setChecked(false);
            m_isCNTime = false;
        }
        this->updateTime();
    });

    // 初始化时间显示
    updateTime();

    this->setFixedWidth(200);
}

TimeDisplayItem::~TimeDisplayItem() {
}

void TimeDisplayItem::updateTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString region = m_isCNTime ? "CN" : "US";
    if (m_isCNTime) {
        currentTime = currentTime.toTimeSpec(Qt::UTC).addSecs(8 * 3600); // 北京时间
    }
    else {
        currentTime = currentTime.toTimeSpec(Qt::UTC).addSecs(-5 * 3600); // 美东时间
    }
    m_timeLabel->setText(region + " " + currentTime.toString("yyyy/MM/dd hh:mm:ss"));
}

void TimeDisplayItem::mousePressEvent(QMouseEvent* event) {
    if (m_popupWidget->isVisible()) {
        m_popupWidget->hide();
    }
    else {
        m_popupWidget->move(event->globalPos());
        m_popupWidget->show();
    }
    QWidget::mousePressEvent(event);
}

void TimeDisplayItem::onPopupClosed() {
    m_popupWidget->hide();
}
