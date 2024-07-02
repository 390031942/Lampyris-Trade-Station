/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "UI/ConnectDialog.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    ConnectDialog* w = new ConnectDialog;
    w->show();
    return a.mainLoop();
}
