/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QtWidgets/QMainWindow>

// Project Include(s)
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
     explicit MainWindow(QWidget *parent = nullptr);

             ~MainWindow();
private:
    Ui::MainWindowClass ui;
};
