#ifndef MINIMUM_GLOBAL_H
#define MINIMUM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MINIMUM_LIBRARY)
#  define MINIMUMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MINIMUMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MINIMUM_GLOBAL_H
