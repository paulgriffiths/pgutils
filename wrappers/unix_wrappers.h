#ifndef PGUTILS_STD_WRAPPERS_H
#define PGUTILS_STD_WRAPPERS_H

#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <sys/types.h>

pid_t wrapper_fork(const char * file, const int line);

#define xfork() wrapper_fork(__FILE__, __LINE__)

#endif      /*  PGUTILS_STD_WRAPPERS_H  */
