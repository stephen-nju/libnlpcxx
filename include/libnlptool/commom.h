
#ifndef COMMON_H_
#define COMMON_H_

#if defined(_WIN32) && !defined(__CYGWIN__)
#define OS_WIN
#else
#define OS_UNIX
#endif
#endif

#ifdef OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


#endif
