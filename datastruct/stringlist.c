#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "stringlist.h"

#define DEFAULT_LIST_SIZE 8

struct stringlist {
    char ** list;       /*  Pointer to list of strings      */
    size_t size;        /*  Current capacity of list        */
    size_t top;         /*  Lowest empty element of list    */
};

enum list_op {
    LISTOP_INSERT,
    LISTOP_GET,
    LISTOP_REMOVE
};

static struct stringlist * stringlist_allocate(void);
static char ** stringlist_list_allocate(const size_t capacity);
static char ** stringlist_list_reallocate(char ** list, const size_t capacity);
static void stringlist_resize_if_full(StringList list);
static bool stringlist_is_full(StringList list);
static void stringlist_error_if_empty(StringList list, const char * msg);
static void stringlist_error_if_range_error(StringList list,
                                            const enum list_op op,
                                            const char * msg,
                                            const size_t index);
static bool stringlist_is_index_in_range(StringList list, const size_t index,
                                         const enum list_op op);
static char * duplicate_string(const char * str);

/*  Creates a new list of default capacity  */

StringList stringlist_create(void)
{
    struct stringlist * new_list = stringlist_allocate();
    new_list->size = DEFAULT_LIST_SIZE;
    new_list->top = 0;
    new_list->list = stringlist_list_allocate(new_list->size);
    return new_list;
}

/*  Destroys the list and frees all resources  */

void stringlist_destroy(StringList list)
{
    for ( size_t i = 0; list->list[i]; ++i ) {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
}

void stringlist_prepend(StringList list, const char * str)
{
    stringlist_insert(list, 0, str);
}

void stringlist_append(StringList list, const char * str)
{
    stringlist_insert(list, list->top, str);
}

void stringlist_insert(StringList list, const size_t index, const char * str)
{
    stringlist_error_if_range_error(list, LISTOP_INSERT,
                                    "couldn't insert string", index);
    stringlist_resize_if_full(list);

    char * duped = duplicate_string(str);
    if ( index == list->top ) {
        list->list[list->top++] = duped;
        list->list[list->top] = NULL;
    }
    else {
        memmove(list->list + index + 1, list->list + index,
                (list->top + 1 - index) * sizeof(*list->list));
        list->list[index] = duped;
        list->top += 1;
    }
}

void stringlist_delete_first(StringList list)
{
    free(stringlist_remove_first(list));
}

void stringlist_delete_last(StringList list)
{
    free(stringlist_remove_last(list));
}

void stringlist_delete_index(StringList list, const size_t index)
{
    free(stringlist_remove_index(list, index));
}

char * stringlist_remove_first(StringList list)
{
    stringlist_error_if_empty(list, "couldn't remove first string");
    return stringlist_remove_index(list, 0);
}

char * stringlist_remove_last(StringList list)
{
    stringlist_error_if_empty(list, "couldn't remove last string");
    return stringlist_remove_index(list, list->top - 1);
}

char * stringlist_remove_index(StringList list, const size_t index)
{
    stringlist_error_if_range_error(list, LISTOP_REMOVE,
                                    "couldn't remove string", index);
    char * removed = list->list[index];
    memmove(list->list + index, list->list + index + 1,
            (list->top - index) * sizeof(*list->list));
    --list->top;

    return removed;
}

char * stringlist_get_first(StringList list)
{
    stringlist_error_if_empty(list, "couldn't get first string");
    return stringlist_get_index(list, 0);
}

char * stringlist_get_last(StringList list)
{
    stringlist_error_if_empty(list, "couldn't get last string");
    return stringlist_get_index(list, list->top - 1);
}

char * stringlist_get_index(StringList list, const size_t index)
{
    stringlist_error_if_range_error(list, LISTOP_GET,
                                    "couldn't get string", index);
    return list->list[index];
}

size_t stringlist_length(StringList list)
{
    return list->top;
}

bool stringlist_is_empty(StringList list)
{
    return list->top == 0;
}

static bool stringlist_is_index_in_range(StringList list, const size_t index,
                                         const enum list_op op)
{
    if ( op == LISTOP_INSERT ) {
        return index <= list->top;
    }
    else {
        return index < list->top;
    }
}

/*  Returns a pointer to the raw list of strings.
 *
 *  This raw list will be NULL-terminated, that is, if the raw
 *  list contains `length` strings, then raw_list[length] == NULL.
 *  This makes the raw list suitable for passing, for instance, to
 *  execv() and friends.
 */

char ** stringlist_raw_list(StringList list)
{
    return list->list;
}

static struct stringlist * stringlist_allocate(void)
{
    struct stringlist * new_list = malloc(sizeof *new_list);
    if ( !new_list ) {
        fprintf(stderr, "Error: couldn't create string list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_list;
}

static char ** stringlist_list_allocate(const size_t capacity)
{
    char ** new_list = calloc(capacity, sizeof *new_list);
    if ( !new_list ) {
        fprintf(stderr, "Error: couldn't create string list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_list;
}

static char ** stringlist_list_reallocate(char ** list, const size_t capacity)
{
    char ** new_list = realloc(list, capacity * sizeof *new_list);
    if ( !new_list ) {
        fprintf(stderr, "Error: couldn't resize string list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_list;
}

static bool stringlist_is_full(StringList list)
{
    return (list->top + 1) >= list->size;
}

static void stringlist_resize_if_full(StringList list)
{
    if ( stringlist_is_full(list) ) {
        list->size *= 2;
        list->list = stringlist_list_reallocate(list->list, list->size);
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

static void stringlist_error_if_empty(StringList list, const char * msg)
{
    if ( stringlist_is_empty(list) ) {
        fprintf(stderr, "Error: %s: %s, line %d\n    string list is empty\n",
                msg, __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}

static void stringlist_error_if_range_error(StringList list,
                                            const enum list_op op,
                                            const char * msg,
                                            const size_t index)
{
    if ( !stringlist_is_index_in_range(list, index, op) ) {
        fprintf(stderr, "Error: %s at index %zu: %s, line %d\n"
                "    index out of range, length %zu\n",
                msg, index, __FILE__, __LINE__, list->top);
        exit(EXIT_FAILURE);
    }
}

