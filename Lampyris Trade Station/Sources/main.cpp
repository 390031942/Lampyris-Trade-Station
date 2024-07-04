/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "UI/ConnectDialog.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"
#include "UI/MainWindow.h"
#include "Model/Quote/QuoteDatabase.h"
#include "Model/Quote/Provider/EastMoneyQuoteProvider.h"


int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    EastMoneyQuoteProvider provider;
    QuoteDatabase::getInstance()->setIndexBriefQuoteProvider(&provider);

    MainWindow* w = new MainWindow;
    w->show();
    return a.mainLoop();
}
