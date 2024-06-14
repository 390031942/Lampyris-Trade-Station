/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "UI/ConnectDialog.h"
#include "UI/MainWindow.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    ConnectDialog w;
    w.show();
    return a.mainLoop();
}
