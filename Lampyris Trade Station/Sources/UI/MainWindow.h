/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMainWindow>
#include <QStatusBar>

// Project Include(s)
#include "ui_MainWindow.h"

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

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
     explicit MainWindow(QWidget *parent = nullptr);
             ~MainWindow();
private:
    void      initStatusBar();

    Ui::MainWindowClass ui;
};
