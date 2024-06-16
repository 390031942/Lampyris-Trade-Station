/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMainWindow>
#include <QStatusBar>

// Project Include(s)
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
     explicit MainWindow(QWidget *parent = nullptr);
             ~MainWindow();
private:
    void      initStatusBar();

    Ui::MainWindowClass ui;
};
