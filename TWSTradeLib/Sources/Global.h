#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TWSTRADELIB_LIB)
#  define TWSTRADELIB_EXPORT Q_DECL_EXPORT
# else
#  define TWSTRADELIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define TWSTRADELIB_EXPORT
#endif
