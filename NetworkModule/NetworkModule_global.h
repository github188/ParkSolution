#ifndef NETWORKMODULE_GLOBAL_H
#define NETWORKMODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETWORKMODULE_LIBRARY)
#  define NETWORKMODULESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NETWORKMODULESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NETWORKMODULE_GLOBAL_H
