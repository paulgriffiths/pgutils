#ifndef PGUTILS_DICTSTRING_H
#define PGUTILS_DICTSTRING_H

#include <stddef.h>
#include <stdbool.h>

typedef struct dictstring * DictString;

DictString dictstring_create(void);
void dictstring_destroy(DictString list);

void dictstring_insert(DictString list, const char * key, const char * value);
char * dictstring_remove(DictString list, const char * key);
bool dictstring_delete(DictString list, const char * key);

bool dictstring_has_key(DictString list, const char * key);
char * dictstring_value_for_key(DictString list, const char * key);

#endif      /*  PGUTILS_DICTSTRING_H  */
