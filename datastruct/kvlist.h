#ifndef PGUTILS_KVLIST_H
#define PGUTILS_KVLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct kvlist * KVList;

KVList kvlist_create(void);
void kvlist_destroy(KVList list);

void kvlist_insert(KVList list, const char * key, const char * value);
char * kvlist_remove(KVList list, const char * key);
bool kvlist_delete(KVList list, const char * key);

bool kvlist_has_key(KVList list, const char * key);
char * kvlist_value_for_key(KVList list, const char * key);

bool kvlist_is_empty(KVList list);
size_t kvlist_length(KVList list);

#endif      /*  PGUTILS_KVLIST_H  */
