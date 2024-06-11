/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
     MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private:
    Ui::MainWindowClass ui;
};
