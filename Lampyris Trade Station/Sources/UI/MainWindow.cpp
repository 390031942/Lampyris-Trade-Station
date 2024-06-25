/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MainWindow.h"
#include <Core/Application.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    this->setWindowTitle(Application::getAppName());
}

MainWindow::~MainWindow() {

}

void MainWindow::initStatusBar() {

}
