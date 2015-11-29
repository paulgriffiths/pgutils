#include <stdio.h>
#include <stdlib.h>
#include "datastruct/dictstring.h"
#include "testing/testing.h"

static void test_dictstring_basic(void);
static void test_dictstring_removing(void);

int main(void)
{
    test_dictstring_basic();
    test_dictstring_removing();
    tests_show_summary();
    return 0;
}

static void test_dictstring_basic(void)
{
    DictString list = dictstring_create();

    dictstring_insert(list, "key one", "value one");
    PGTEST_TRUE(dictstring_has_key(list, "key one"));
    PGTEST_FALSE(dictstring_has_key(list, "key two"));
    PGTEST_FALSE(dictstring_has_key(list, "key three"));
    PGTEST_STREQUAL("value one", dictstring_value_for_key(list, "key one"));

    dictstring_insert(list, "key two", "value two");
    PGTEST_TRUE(dictstring_has_key(list, "key one"));
    PGTEST_TRUE(dictstring_has_key(list, "key two"));
    PGTEST_FALSE(dictstring_has_key(list, "key three"));
    PGTEST_STREQUAL("value one", dictstring_value_for_key(list, "key one"));
    PGTEST_STREQUAL("value two", dictstring_value_for_key(list, "key two"));

    dictstring_insert(list, "key one", "value three");
    PGTEST_TRUE(dictstring_has_key(list, "key one"));
    PGTEST_TRUE(dictstring_has_key(list, "key two"));
    PGTEST_FALSE(dictstring_has_key(list, "key three"));
    PGTEST_STREQUAL("value three", dictstring_value_for_key(list, "key one"));
    PGTEST_STREQUAL("value two", dictstring_value_for_key(list, "key two"));

    dictstring_destroy(list);
}

static void test_dictstring_removing(void)
{
    DictString list = dictstring_create();
    
    dictstring_insert(list, "key one", "value one");
    dictstring_insert(list, "key two", "value two");
    dictstring_insert(list, "key three", "value three");

    char * removed = dictstring_remove(list, "key four");
    PGTEST_FALSE(removed);

    removed = dictstring_remove(list, "key two");
    PGTEST_STREQUAL("value two", removed);
    free(removed);

    PGTEST_FALSE(dictstring_delete(list, "key five"));
    PGTEST_TRUE(dictstring_delete(list, "key one"));

    dictstring_destroy(list);
}
