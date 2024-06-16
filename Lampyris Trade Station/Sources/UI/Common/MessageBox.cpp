/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MessageBox.h"

void SingletonImpl::MessageBoxClass::info(const QString& info) {
	QMessageBox::information(NULL, "Lampyris Trade Station", info);
}

void SingletonImpl::MessageBoxClass::warning(const QString& warn) {
	QMessageBox::warning(NULL, "Lampyris Trade Station", warn);
}

void SingletonImpl::MessageBoxClass::error(const QString& error) {
	QMessageBox::critical(NULL, "Lampyris Trade Station", error);
}