#pragma once

#include <QtGlobal>

#if defined(LMQSL_LIBRARY)
#  define LMQSLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LMQSLSHARED_EXPORT Q_DECL_IMPORT
#endif
