/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MainWindowStatusBar.h"
#include <Base/Localization.h>
#include <Model/UI/IndexBriefQuoteSubscription.h>
#include "StatusBar/IndexBriefQuoteItem.h"
#include "StatusBar/ConnectionStatusItem.h"
#include "StatusBar/TimeDisplayItem.h"

// QT Include(s)
#include <QSizeGrip>
#include <qsplitter.h>
#include <QPushButton>

MainWindowStatusBar::MainWindowStatusBar(QWidget* parent) {
	this->setFixedHeight(30);
	this->setContentsMargins(0,0,0,0);
	this->createIndexBriefQuotePart();
	this->createLogButtonPart();
	this->createConnectionStatusPart();
	this->createTimeDisplayPart();
}

MainWindowStatusBar::~MainWindowStatusBar() {
}

void MainWindowStatusBar::createIndexBriefQuotePart() {
	// 根据订阅的 指数简要行情 的数量 来创建IndexBriefQuoteItem
	const auto list = IndexBriefQuoteSubscription::getInstance()->getSubscribedList();
	this->m_indexBriefQuoteItemList.clear();
	this->m_indexBriefQuoteItemList.reserve(list.size());

	QWidget* containerWidget = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(3);
	containerWidget->setLayout(layout);

	for (int i = 0; i < list.size(); i++) {
		auto item = new IndexBriefQuoteItem(this);
		layout->addWidget(item);
		item->subscribe(list[i]);
		this->m_indexBriefQuoteItemList.push_back(item);
	}

	this->addPermanentWidget(containerWidget, 0);
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createLogButtonPart() {
	QPushButton* button = new QPushButton(this);
	button->setFixedWidth(100);
	button->setText(Localization->get("StatusBar_1"));
	QObject::connect(button, &QPushButton::clicked, [=]() {
		
	});
	this->addPermanentWidget(button,1);
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createConnectionStatusPart() {
	ConnectionStatusItem* item = new ConnectionStatusItem(this);
	this->addPermanentWidget(item, 2);
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createTimeDisplayPart() {
	TimeDisplayItem* item = new TimeDisplayItem(this);
	this->addPermanentWidget(item, 4);
}
