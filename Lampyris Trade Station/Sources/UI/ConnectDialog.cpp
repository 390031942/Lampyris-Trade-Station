/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectDialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);
	ui.LoginGif->setGifImagePath(":/Resources/Gif/Gif_0004.gif");
}

ConnectDialog::~ConnectDialog() {
}
