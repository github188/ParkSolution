#ifndef DATAPARSE_GLOBAL_H
#define DATAPARSE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATAPARSE_LIBRARY)
#  define DATAPARSESHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATAPARSESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATAPARSE_GLOBAL_H
