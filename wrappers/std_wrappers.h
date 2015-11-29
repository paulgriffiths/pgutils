#ifndef PGUTILS_STD_WRAPPERS_H
#define PGUTILS_STD_WRAPPERS_H

#include <stddef.h>

void * wrapper_malloc(const size_t size, const char * file, const int line);
void * wrapper_realloc(void * ptr, const size_t size,
                       const char * file, const int line);
void * wrapper_calloc(const size_t count, const size_t size,
                      const char * file, const int line);
char * wrapper_strdup(const char * str, const char * file, const int line);

#define xmalloc(size) wrapper_malloc((size), __FILE__, __LINE__)
#define xrealloc(ptr, size) wrapper_realloc((ptr), (size), __FILE__, __LINE__)
#define xcalloc(count, size) wrapper_calloc((count), (size), __FILE__, __LINE__)
#define xstrdup(str) wrapper_strdup((str), __FILE__, __LINE__)

#endif      /*  PGUTILS_STD_WRAPPERS_H  */
