#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dictstring.h"
#include "kvlist.h"

#define NUMBER_BUCKETS 256

struct dictstring {
    KVList * lists;
    size_t num_buckets;
};

static struct dictstring * dictstring_allocate(void);
static KVList * dictstring_lists_allocate(const size_t capacity);
static size_t djb2hash(const char * str);

DictString dictstring_create(void)
{
    struct dictstring * new_dict = dictstring_allocate();
    new_dict->num_buckets = NUMBER_BUCKETS;
    new_dict->lists = dictstring_lists_allocate(new_dict->num_buckets);
    return new_dict;
}

void dictstring_destroy(DictString dict)
{
    for ( size_t i = 0; i < dict->num_buckets; ++i ) {
        kvlist_destroy(dict->lists[i]);
    }
    free(dict->lists);
    free(dict);
}

void dictstring_insert(DictString dict, const char * key, const char * value)
{
    const size_t hash = djb2hash(key) % dict->num_buckets;
    kvlist_insert(dict->lists[hash], key, value);
}

char * dictstring_remove(DictString dict, const char * key)
{
    const size_t hash = djb2hash(key) % dict->num_buckets;
    return kvlist_remove(dict->lists[hash], key);
}

bool dictstring_delete(DictString dict, const char * key)
{
    const size_t hash = djb2hash(key) % dict->num_buckets;
    return kvlist_delete(dict->lists[hash], key);
}

bool dictstring_has_key(DictString dict, const char * key)
{
    const size_t hash = djb2hash(key) % dict->num_buckets;
    return kvlist_has_key(dict->lists[hash], key);
}

char * dictstring_value_for_key(DictString dict, const char * key)
{
    const size_t hash = djb2hash(key) % dict->num_buckets;
    return kvlist_value_for_key(dict->lists[hash], key);
}

static struct dictstring * dictstring_allocate(void)
{
    struct dictstring * new_dict = malloc(sizeof *new_dict);
    if ( !new_dict ) {
        fprintf(stderr, "Error: couldn't create string dictionary: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_dict;
}

static KVList * dictstring_lists_allocate(const size_t capacity)
{
    KVList * new_lists = malloc(capacity * sizeof *new_lists);
    if ( !new_lists ) {
        fprintf(stderr, "Error: couldn't create key-value lists: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    for ( size_t i = 0; i < capacity; ++i ) {
        new_lists[i] = kvlist_create();
    }

    return new_lists;
}

static size_t djb2hash(const char * str)
{
    size_t hash = 5381;
    int c;

    while ( (c = *str++) ) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
