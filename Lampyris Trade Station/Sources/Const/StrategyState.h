/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

enum StrategyState {
    NotActive = 0,
    WaitForTime = 1,
    Active = 2,
    Finished = 3,
};