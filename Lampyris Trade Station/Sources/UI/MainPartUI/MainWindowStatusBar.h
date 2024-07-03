/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QStatusBar>

// Project Include(s)
#include "StatusBar/IndexBriefQuoteItem.h"

class MainWindowStatusBar : public QStatusBar {
    typedef std::vector<IndexBriefQuoteItem*> QuoteItemList;
    Q_OBJECT
public:
    explicit      MainWindowStatusBar(QWidget* parent = nullptr);
                 ~MainWindowStatusBar();
private:         
    void          createIndexBriefQuotePart();
    void          createLogButtonPart();
    void          createConnectionStatusPart();
    void          createTimeDisplayPart();

    QuoteItemList m_indexBriefQuoteItemList;
};