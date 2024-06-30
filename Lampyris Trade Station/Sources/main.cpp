/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "UI/ConnectDialog.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"
#include <UI/Tips/OrderFilledTips.h>

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    // OrderFilledTips::getInstance()->show("NIVF", "BUY", 10.00, 30000);
    // 
    // OrderFilledTipsConnectDialog* w = new ConnectDialog;
    // w->show();
    return a.mainLoop();
}
