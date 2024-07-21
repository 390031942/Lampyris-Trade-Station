/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Base/Localization.h"
#include "Core/Application.h"
#include "Const/AppReturnCode.h"
#include "UI/ConnectDialog.h"
#include "UI/Common/MessageBox.h"

int main(int argc, char *argv[]) {
    Application a(argc, argv);

    if (!a.createAppInstanceMutex()) {
        MessageBox->error(Localization->get("AppReturnTips_AppInstanceAlreadyExists"));
        return AppReturnCode::AppInstanceAlreadyExists;
    }

    ConnectDialog * w = new ConnectDialog;
    w->show();
    return a.mainLoop();
}
