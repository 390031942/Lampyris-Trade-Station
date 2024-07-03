/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MainWindowStatusBar.h"
#include <Model/UI/IndexBriefQuoteSubscription.h>

// QT Include(s)
#include <QSizeGrip>
#include <qsplitter.h>
#include <QPushButton>

MainWindowStatusBar::MainWindowStatusBar(QWidget* parent) {
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
	containerWidget->setLayout(layout);
	layout->setContentsMargins(0, 0, 0, 0);

	for (int i = 0; i < list.size(); i++) {
		auto item = new IndexBriefQuoteItem(this);
		item->subscribe(list[i]);
		this->m_indexBriefQuoteItemList.push_back(item);
		layout->addWidget(item);

		if (i == 0) { /** containerWidget的宽度高度由IndexBriefQuoteItem数量决定 */
			containerWidget->setFixedSize(item->width() * list.size(), item->height());
		}
	}

	this->addPermanentWidget(containerWidget, 0);
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createLogButtonPart() {
	QPushButton* button = new QPushButton(this);
	QObject::connect(button, &QPushButton::clicked, [=]() {
		
	});
	this->addPermanentWidget(button,1);
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createConnectionStatusPart() {
	this->addPermanentWidget(new QSplitter(Qt::Orientation::Vertical, this));
}

void MainWindowStatusBar::createTimeDisplayPart() {
}
