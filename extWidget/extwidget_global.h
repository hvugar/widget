#ifndef EXTWIDGET_GLOBAL_H
#define EXTWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXT_WIDGET_LIBRARY)
#  define EXT_WIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EXT_WIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EXTWIDGET_GLOBAL_H
