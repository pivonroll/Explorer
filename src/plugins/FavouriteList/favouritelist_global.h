#ifndef FAVOURITELIST_GLOBAL_H
#define FAVOURITELIST_GLOBAL_H

#include <QtGlobal>

#if defined(FAVOURITELIST_LIBRARY)
#  define FAVOURITELISTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FAVOURITELISTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FAVOURITELIST_GLOBAL_H

