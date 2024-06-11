/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#ifndef LTS_SAFE_DELETE
 #define LTS_SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#endif // !LTS_SAFE_DELETE

#ifndef LTS_SAFE_DELETE_ARRAY
#define LTS_SAFE_DELETE_ARRAY(p) if(p) {delete []p; p = nullptr;}
#endif // !LTS_SAFE_DELETE_ARRAY