/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#ifndef LAMPYRIS_NEW
#define LAMPYRIS_NEW(T,...) new T(__VA_ARGS__) 
#endif // !LAMPYRIS_NEW

#ifndef LAMPYRIS_NEW_ARRAY
#define LAMPYRIS_NEW_ARRAY(T,n) new T[n]
#endif // !LAMPYRIS_NEW_ARRAY

#ifndef LAMPYRIS_SAFE_DELETE
 #define LAMPYRIS_SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#endif // !LAMPYRIS_SAFE_DELETE

#ifndef LAMPYRIS_SAFE_DELETE_ARRAY
#define LAMPYRIS_SAFE_DELETE_ARRAY(p) if(p) {delete []p; p = nullptr;}
#endif // !LAMPYRIS_SAFE_DELETE_ARRAY