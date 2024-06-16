/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QHistoryRecordLineEdit.h"

QHistoryRecordLineEdit::QHistoryRecordLineEdit(QWidget* parent) : QWidget(parent) {
    setupUI();
}

void QHistoryRecordLineEdit::clearHistory() {
    m_completer->model()->removeRows(0, m_completer->model()->rowCount());
}

void QHistoryRecordLineEdit::showHistory() {
    // 显示历史记录
    m_completer->complete();
}

void QHistoryRecordLineEdit::setupUI() {
    m_lineEdit = new QLineEdit(this);
    m_completer = new QCompleter(this);
    m_menu = new QMenu(this);

    // 添加历史记录到QCompleter
    m_completer->setModelSorting(QCompleter::UnsortedModel);
    m_completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

    // 添加清空历史记录的按钮
    QAction* clearAction = m_menu->addAction("clear all");
    connect(clearAction, &QAction::triggered, this, &QHistoryRecordLineEdit::clearHistory);

    // 将QCompleter和QLineEdit关联
    m_lineEdit->setCompleter(m_completer);

    // 添加按钮到QLineEdit右侧
    QPushButton* button = new QPushButton("H", this);
    button->setFixedWidth(20);
    connect(button, &QPushButton::clicked, this, &QHistoryRecordLineEdit::showHistory);

    // 布局
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->addWidget(button);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->setSpacing(3); 

    // 模拟添加历史记录
    m_history.append("History 1");
    m_history.append("History 2");
    m_history.append("History 3");

    m_completer->setModel(new QStringListModel(m_history, m_completer));

    connect(m_completer, static_cast<void (QCompleter::*)(const QString&)>(&QCompleter::activated),
            this, &QHistoryRecordLineEdit::onCompleterActivated);
}

void QHistoryRecordLineEdit::onCompleterActivated(const QString& text) {
    m_lineEdit->setText(text);
}