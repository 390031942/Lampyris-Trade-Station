/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QApplication>
#include <QLineEdit>
#include <QCompleter>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QStringListModel>

// Project Include(s)
#include <Interface/ISerializable.h>

class QHistoryRecordLineEdit : public QWidget {
    Q_OBJECT
public:
                   QHistoryRecordLineEdit(QWidget* parent = nullptr);
private:           
    void           showHistory();
    void           clearHistory();
private slots:
    void           onCompleterActivated(const QString& text);
private:
    void           setupUI();
    QLineEdit*     m_lineEdit;
    QCompleter*    m_completer;
    QMenu*         m_menu;
    QStringList    m_history;
    ISerializable* m_serializable;
};