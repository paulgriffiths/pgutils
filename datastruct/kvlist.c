#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kvlist.h"
#include "stringpair.h"

#define INITIAL_LIST_SIZE 8

struct kvlist {
    StringPair * pairs;
    size_t capacity;
    size_t top;
};

static struct kvlist * kvlist_allocate(void);
static StringPair * kvlist_pairs_allocate(const size_t capacity);
static StringPair * kvlist_pairs_reallocate(StringPair * pairs,
                                            const size_t capacity);
static void kvlist_resize_if_necessary(KVList list);
static bool kvlist_index_of_key(KVList list, const char * key, size_t * index);
static char * kvlist_remove_at_index(KVList list, const size_t index);
static void kvlist_delete_at_index(KVList list, const size_t index);
static bool kvlist_is_full(KVList list);
static char * duplicate_string(const char * str);

KVList kvlist_create(void)
{
    struct kvlist * new_list = kvlist_allocate();
    new_list->capacity = INITIAL_LIST_SIZE;
    new_list->top = 0;
    new_list->pairs = kvlist_pairs_allocate(new_list->capacity);
    return new_list;
}

void kvlist_destroy(KVList list)
{
    for ( size_t i = 0; i < list->top; ++i ) {
        stringpair_destroy(list->pairs[i]);
    }
    free(list->pairs);
    free(list);
}

void kvlist_insert(KVList list, const char * key, const char * value)
{
    StringPair new_pair = stringpair_create(key, value);

    size_t index;
    if ( kvlist_index_of_key(list, key, &index) ) {
        stringpair_destroy(list->pairs[index]);
        list->pairs[index] = new_pair;
    }
    else {
        kvlist_resize_if_necessary(list);
        list->pairs[list->top++] = new_pair;
    }
}

char * kvlist_remove(KVList list, const char * key)
{
    size_t index;
    if ( kvlist_index_of_key(list, key, &index) ) {
        return kvlist_remove_at_index(list, index);
    }
    else {
        return NULL;
    }
}

bool kvlist_delete(KVList list, const char * key)
{
    size_t index;
    if ( kvlist_index_of_key(list, key, &index) ) {
        kvlist_delete_at_index(list, index);
        return true;
    }
    else {
        return false;
    }
}

static char * kvlist_remove_at_index(KVList list, const size_t index)
{
    char * removed = duplicate_string(stringpair_second(list->pairs[index]));
    kvlist_delete_at_index(list, index);
    return removed;
}

static void kvlist_delete_at_index(KVList list, const size_t index)
{
    stringpair_destroy(list->pairs[index]);
    memmove(list->pairs + index, list->pairs + index + 1,
            (list->top - index - 1) * sizeof *list->pairs);
    --list->top;
}

static bool kvlist_index_of_key(KVList list, const char * key, size_t * index)
{
    for ( size_t i = 0; i < list->top; ++i ) {
        if ( !strcmp(key, stringpair_first(list->pairs[i])) ) {
            if ( index ) {
                *index = i;
            }
            return true;
        }
    }
    return false;
}

bool kvlist_has_key(KVList list, const char * key)
{
    return kvlist_index_of_key(list, key, NULL);
}

char * kvlist_value_for_key(KVList list, const char * key)
{
    size_t index;
    if ( kvlist_index_of_key(list, key, &index) ) {
        return stringpair_second(list->pairs[index]);
    }
    else {
        return NULL;
    }
}

bool kvlist_is_empty(KVList list)
{
    return list->top == 0;
}

static bool kvlist_is_full(KVList list)
{
    return list->top == list->capacity;
}

size_t kvlist_length(KVList list)
{
    return list->top;
}

static struct kvlist * kvlist_allocate(void)
{
    struct kvlist * new_list = malloc(sizeof *new_list);
    if ( !new_list ) {
        fprintf(stderr, "Error: couldn't create key-value list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_list;
}

static StringPair * kvlist_pairs_allocate(const size_t capacity)
{
    StringPair * new_pairs = malloc(capacity * sizeof *new_pairs);
    if ( !new_pairs ) {
        fprintf(stderr, "Error: couldn't create key-value pairs list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_pairs;
}

static StringPair * kvlist_pairs_reallocate(StringPair * pairs,
                                            const size_t capacity)
{
    StringPair * new_pairs = realloc(pairs, capacity * sizeof *new_pairs);
    if ( !new_pairs ) {
        fprintf(stderr, "Error: couldn't create key-value pairs list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_pairs;
}

static void kvlist_resize_if_necessary(KVList list)
{
    if ( kvlist_is_full(list) ) {
        list->capacity *= 2;
        list->pairs = kvlist_pairs_reallocate(list->pairs, list->capacity);
    }
}

static char * duplicate_string(const char * str)
{
    char * new_string = malloc(strlen(str) + 1);
    if ( !new_string ) {
        fprintf(stderr, "Error: couldn't duplicate string: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    strcpy(new_string, str);
    return new_string;
}
