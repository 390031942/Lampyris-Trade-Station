/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "UI/ConnectDialog.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"
#include "UI/MainPartUI/StatusBar/ConnectionStatusItem.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    ConnectionStatusItem* w = new ConnectionStatusItem;
    w->show();
    return a.mainLoop();
}
