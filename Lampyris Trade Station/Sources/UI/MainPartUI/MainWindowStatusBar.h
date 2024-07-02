/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QStatusBar>

// Project Include(s)
#include "StatusBar/IndexBriefQuoteItem.h"

class MainWindowStatusBar : public QStatusBar {
    Q_OBJECT
public:
    explicit MainWindowStatusBar(QWidget* parent = nullptr);
    ~MainWindowStatusBar();
private:
    void initIndexBriefQuotePart();
};