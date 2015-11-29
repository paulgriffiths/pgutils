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


/*  Creates a new list of default capacity  */

StringList stringlist_create(void)
{
    struct stringlist * new_list = malloc(sizeof *new_list);
    if ( !new_list ) {
        fprintf(stderr, "Error: couldn't create string list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    new_list->size = DEFAULT_LIST_SIZE;
    new_list->top = 0;

    char ** list = calloc(new_list->size, sizeof *list);
    if ( !list ) {
        fprintf(stderr, "Error: couldn't create string list: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    new_list->list = list;

    return new_list;
}

/*  Destroys the list and frees all resources  */

void stringlist_destroy(StringList list)
{
    while ( !stringlist_is_empty(list) ) {
        stringlist_delete_first(list);
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
    if ( index > list->top ) {
        fprintf(stderr, "Error: couldn't insert string at index %zu: "
                "%s, line %d\n    index out of range, length %zu\n",
                index, __FILE__, __LINE__, list->top);
        exit(EXIT_FAILURE);
    }

    if ( list->top + 1 >= list->size ) {
        char ** new_array = realloc(list->list,
                                    list->size * 2 * sizeof *new_array);
        if ( !new_array ) {
            fprintf(stderr, "Error: couldn't resize string list: "
                    "%s, line %d\n    %s (%d)\n",
                    __FILE__, __LINE__, strerror(errno), errno);
            exit(EXIT_FAILURE);
        }
        list->list = new_array;
        list->size *= 2;
    }

    char * duped = malloc(strlen(str) + 1);
    if ( !duped ) {
        fprintf(stderr, "Error: couldn't duplicate string: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    strcpy(duped, str);

    if ( index == list->top ) {
        list->list[list->top] = duped;
        list->top += 1;
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
    if ( stringlist_is_empty(list) ) {
        fprintf(stderr, "Error: couldn't remove first string: "
                "%s, line %d\n    string list is empty\n",
                __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    else {
        return stringlist_remove_index(list, 0);
    }
}

char * stringlist_remove_last(StringList list)
{
    if ( stringlist_is_empty(list) ) {
        fprintf(stderr, "Error: couldn't remove last string: "
                "%s, line %d\n    string list is empty\n",
                __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    else {
        return stringlist_remove_index(list, list->top - 1);
    }
}

char * stringlist_remove_index(StringList list, const size_t index)
{
    if ( !stringlist_is_index_in_range(list, index) ) {
        fprintf(stderr, "Error: couldn't remove string at index %zu: "
                "%s, line %d\n    index out of range, length is %zu\n",
                index, __FILE__, __LINE__, list->top);
        exit(EXIT_FAILURE);
    }

    char * removed = list->list[index];
    memmove(list->list + index, list->list + index + 1,
            (list->top - index) * sizeof(*list->list));
    list->top -= 1;

    return removed;
}

char * stringlist_get_first(StringList list)
{
    if ( stringlist_is_empty(list) ) {
        fprintf(stderr, "Error: couldn't get first string: "
                "%s, line %d\n    string list is empty\n",
                __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    else {
        return stringlist_get_index(list, 0);
    }
}

char * stringlist_get_last(StringList list)
{
    if ( stringlist_is_empty(list) ) {
        fprintf(stderr, "Error: couldn't get last string: "
                "%s, line %d\n    string list is empty\n",
                __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    else {
        return stringlist_get_index(list, list->top - 1);
    }
}

char * stringlist_get_index(StringList list, const size_t index)
{
    if ( !stringlist_is_index_in_range(list, index) ) {
        fprintf(stderr, "Error: couldn't get string at index %zu: "
                "%s, line %d\n    index out of range, length is %zu\n",
                index, __FILE__, __LINE__, list->top);
        exit(EXIT_FAILURE);
    }
    else {
        return list->list[index];
    }
}

size_t stringlist_length(StringList list)
{
    return list->top;
}

bool stringlist_is_empty(StringList list)
{
    return list->top == 0;
}

bool stringlist_is_index_in_range(StringList list, const size_t index)
{
    return index < list->top;
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
