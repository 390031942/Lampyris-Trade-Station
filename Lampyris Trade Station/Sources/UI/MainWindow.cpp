/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MainWindow.h"
#include <Core/Application.h>

MainWindow::MainWindow(QWidget *parent) {
    ui.setupUi(this);

    this->setParent(parent);
    this->setWindowTitle(Application::getAppName());
}

MainWindow::~MainWindow() {
    
}