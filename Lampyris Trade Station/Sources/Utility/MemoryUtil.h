/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#ifndef LAMPYRIS_SAFE_DELETE
 #define LAMPYRIS_SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#endif // !LAMPYRIS_SAFE_DELETE

#ifndef LAMPYRIS_SAFE_DELETE_ARRAY
#define LAMPYRIS_SAFE_DELETE_ARRAY(p) if(p) {delete []p; p = nullptr;}
#endif // !LAMPYRIS_SAFE_DELETE_ARRAY