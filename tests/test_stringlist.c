#include <stdio.h>
#include <stdlib.h>
#include "testing/testing.h"
#include "datastruct/stringlist.h"

static void test_stringlist_inserting(void);
static void test_stringlist_inserting_many(void);
static void test_stringlist_removing(void);
static void test_stringlist_deleting(void);

int main(void)
{
    test_stringlist_inserting();
    test_stringlist_inserting_many();
    test_stringlist_removing();
    test_stringlist_deleting();
    tests_show_summary();
    return 0;
}


static void test_stringlist_inserting(void)
{
    StringList list = stringlist_create();
    PGTEST_EQUAL(0, stringlist_length(list));

    char ** rawlist = stringlist_raw_list(list);
    PGTEST(rawlist[0] == NULL);

    stringlist_insert(list, 0, "string one");
    PGTEST_EQUAL(1, stringlist_length(list));

    rawlist = stringlist_raw_list(list);
    PGTEST_STREQUAL(rawlist[0], "string one");
    PGTEST(rawlist[1] == NULL);

    stringlist_insert(list, 0, "string two");
    PGTEST_EQUAL(2, stringlist_length(list));

    rawlist = stringlist_raw_list(list);
    PGTEST_STREQUAL(rawlist[0], "string two");
    PGTEST_STREQUAL(rawlist[1], "string one");
    PGTEST(rawlist[2] == NULL);

    stringlist_insert(list, 2, "string three");
    PGTEST_EQUAL(3, stringlist_length(list));

    rawlist = stringlist_raw_list(list);
    PGTEST_STREQUAL(rawlist[0], "string two");
    PGTEST_STREQUAL(rawlist[1], "string one");
    PGTEST_STREQUAL(rawlist[2], "string three");
    PGTEST(rawlist[3] == NULL);

    stringlist_prepend(list, "string four");
    PGTEST_EQUAL(4, stringlist_length(list));

    rawlist = stringlist_raw_list(list);
    PGTEST_STREQUAL(rawlist[0], "string four");
    PGTEST_STREQUAL(rawlist[1], "string two");
    PGTEST_STREQUAL(rawlist[2], "string one");
    PGTEST_STREQUAL(rawlist[3], "string three");
    PGTEST(rawlist[4] == NULL);

    stringlist_append(list, "string five");
    PGTEST_EQUAL(5, stringlist_length(list));

    rawlist = stringlist_raw_list(list);
    PGTEST_STREQUAL(rawlist[0], "string four");
    PGTEST_STREQUAL(rawlist[1], "string two");
    PGTEST_STREQUAL(rawlist[2], "string one");
    PGTEST_STREQUAL(rawlist[3], "string three");
    PGTEST_STREQUAL(rawlist[4], "string five");
    PGTEST(rawlist[5] == NULL);

    PGTEST_STREQUAL("string four", stringlist_get_first(list));
    PGTEST_STREQUAL("string two", stringlist_get_index(list, 1));
    PGTEST_STREQUAL("string one", stringlist_get_index(list, 2));
    PGTEST_STREQUAL("string three", stringlist_get_index(list, 3));
    PGTEST_STREQUAL("string five", stringlist_get_last(list));

    stringlist_destroy(list);
}

static void test_stringlist_inserting_many(void)
{
    StringList list = stringlist_create();

    for ( size_t i = 0; i < 1000; ++i ) {
        stringlist_append(list, "a string");
    }
    PGTEST_EQUAL(1000, stringlist_length(list));

    stringlist_destroy(list);
}

static void test_stringlist_removing(void)
{
    StringList list = stringlist_create();

    stringlist_append(list, "string one");
    stringlist_append(list, "string two");
    stringlist_append(list, "string three");
    stringlist_append(list, "string four");
    stringlist_append(list, "string five");

    char * str = stringlist_remove_first(list);
    PGTEST_EQUAL(4, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string three", stringlist_get_index(list, 1));
    PGTEST_STREQUAL("string four", stringlist_get_index(list, 2));
    PGTEST_STREQUAL("string five", stringlist_get_last(list));
    PGTEST_STREQUAL("string one", str);
    free(str);

    str = stringlist_remove_last(list);
    PGTEST_EQUAL(3, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string three", stringlist_get_index(list, 1));
    PGTEST_STREQUAL("string four", stringlist_get_last(list));
    PGTEST_STREQUAL("string five", str);
    free(str);

    str = stringlist_remove_index(list, 1);
    PGTEST_EQUAL(2, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string four", stringlist_get_last(list));
    PGTEST_STREQUAL("string three", str);
    free(str);

    stringlist_destroy(list);
}

static void test_stringlist_deleting(void)
{
    StringList list = stringlist_create();

    stringlist_append(list, "string one");
    stringlist_append(list, "string two");
    stringlist_append(list, "string three");
    stringlist_append(list, "string four");
    stringlist_append(list, "string five");

    stringlist_delete_first(list);
    PGTEST_EQUAL(4, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string three", stringlist_get_index(list, 1));
    PGTEST_STREQUAL("string four", stringlist_get_index(list, 2));
    PGTEST_STREQUAL("string five", stringlist_get_last(list));

    stringlist_delete_last(list);
    PGTEST_EQUAL(3, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string three", stringlist_get_index(list, 1));
    PGTEST_STREQUAL("string four", stringlist_get_last(list));

    stringlist_delete_index(list, 1);
    PGTEST_EQUAL(2, stringlist_length(list));
    PGTEST_STREQUAL("string two", stringlist_get_first(list));
    PGTEST_STREQUAL("string four", stringlist_get_last(list));

    stringlist_destroy(list);
}
