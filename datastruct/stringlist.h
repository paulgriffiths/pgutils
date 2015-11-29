#ifndef PGUTILS_STRINGLIST_H
#define PGUTILS_STRINGLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stringlist * StringList;

StringList stringlist_create(void);
void stringlist_destroy(StringList list);

size_t stringlist_length(StringList list);
bool stringlist_is_empty(StringList list);

void stringlist_prepend(StringList list, const char * str);
void stringlist_append(StringList list, const char * str);
void stringlist_insert(StringList list, const size_t index, const char * str);

void stringlist_delete_first(StringList list);
void stringlist_delete_last(StringList list);
void stringlist_delete_index(StringList list, const size_t index);

char * stringlist_remove_first(StringList list);
char * stringlist_remove_last(StringList list);
char * stringlist_remove_index(StringList list, const size_t index);

char * stringlist_get_first(StringList list);
char * stringlist_get_last(StringList list);
char * stringlist_get_index(StringList list, const size_t index);

char ** stringlist_raw_list(StringList list);

#endif      /*  PGUTILS_STRINGLIST_H  */
