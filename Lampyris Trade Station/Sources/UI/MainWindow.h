/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMainWindow>
#include <QStatusBar>

// Project Include(s)
#include "ui_MainWindow.h"
#include <Base/Singleton.h>

class MainWindow : public SingletonQObject<MainWindow,QMainWindow> {
    Q_OBJECT
public:
     explicit MainWindow(QWidget *parent = nullptr);
             ~MainWindow();
private:
    void      initStatusBar();

    Ui::MainWindowClass ui;
};
