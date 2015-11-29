#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "std_wrappers.h"

void * wrapper_malloc(const size_t size, const char * file, const int line)
{
    void * allocation = malloc(size);
    if ( !allocation ) {
        fprintf(stderr, "Error: couldn't allocate memory: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return allocation;
}

void * wrapper_realloc(void * ptr, const size_t size,
                       const char * file, const int line)
{
    void * allocation = realloc(ptr, size);
    if ( !allocation ) {
        fprintf(stderr, "Error: couldn't reallocate memory: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return allocation;
}

void * wrapper_calloc(const size_t count, const size_t size,
                      const char * file, const int line)
{
    void * allocation = calloc(count, size);
    if ( !allocation ) {
        fprintf(stderr, "Error: couldn't allocate memory: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return allocation;
}

char * wrapper_strdup(const char * str, const char * file, const int line)
{
    char * new_str = wrapper_malloc(strlen(str) + 1, file, line);
    if ( !new_str ) {
        fprintf(stderr, "Error: couldn't allocate memory for string: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    strcpy(new_str, str);
    return new_str;
}
