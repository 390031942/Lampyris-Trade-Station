/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QStatusBar>

class MainWindowStatusBarIndexQuoteItem : public QWidget {
    Q_OBJECT
public:
    explicit MainWindowStatusBarIndexQuoteItem(QWidget* parent = nullptr);
    ~MainWindowStatusBarIndexQuoteItem();
private:
};

class MainWindowStatusBar : public QStatusBar {
    Q_OBJECT
public:
    explicit MainWindowStatusBar(QWidget* parent = nullptr);
    ~MainWindowStatusBar();
private:

};