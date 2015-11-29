#include <stdio.h>
#include <stdlib.h>
#include "datastruct/kvlist.h"
#include "testing/testing.h"

static void test_kvlist_basic(void);
static void test_kvlist_removing(void);
static void test_kvlist_insert_many(void);

int main(void)
{
    test_kvlist_basic();
    test_kvlist_removing();
    test_kvlist_insert_many();
    tests_show_summary();
    return 0;
}

static void test_kvlist_basic(void)
{
    KVList list = kvlist_create();

    PGTEST_EQUAL(0, kvlist_length(list));

    kvlist_insert(list, "key one", "value one");
    PGTEST_EQUAL(1, kvlist_length(list));
    PGTEST_TRUE(kvlist_has_key(list, "key one"));
    PGTEST_FALSE(kvlist_has_key(list, "key two"));
    PGTEST_FALSE(kvlist_has_key(list, "key three"));
    PGTEST_STREQUAL("value one", kvlist_value_for_key(list, "key one"));

    kvlist_insert(list, "key two", "value two");
    PGTEST_EQUAL(2, kvlist_length(list));
    PGTEST_TRUE(kvlist_has_key(list, "key one"));
    PGTEST_TRUE(kvlist_has_key(list, "key two"));
    PGTEST_FALSE(kvlist_has_key(list, "key three"));
    PGTEST_STREQUAL("value one", kvlist_value_for_key(list, "key one"));
    PGTEST_STREQUAL("value two", kvlist_value_for_key(list, "key two"));

    kvlist_insert(list, "key one", "value three");
    PGTEST_EQUAL(2, kvlist_length(list));
    PGTEST_TRUE(kvlist_has_key(list, "key one"));
    PGTEST_TRUE(kvlist_has_key(list, "key two"));
    PGTEST_FALSE(kvlist_has_key(list, "key three"));
    PGTEST_STREQUAL("value three", kvlist_value_for_key(list, "key one"));
    PGTEST_STREQUAL("value two", kvlist_value_for_key(list, "key two"));

    kvlist_destroy(list);
}

static void test_kvlist_removing(void)
{
    KVList list = kvlist_create();
    
    kvlist_insert(list, "key one", "value one");
    kvlist_insert(list, "key two", "value two");
    kvlist_insert(list, "key three", "value three");

    PGTEST_EQUAL(3, kvlist_length(list));

    char * removed = kvlist_remove(list, "key four");
    PGTEST_FALSE(removed);
    PGTEST_EQUAL(3, kvlist_length(list));

    removed = kvlist_remove(list, "key two");
    PGTEST_STREQUAL("value two", removed);
    PGTEST_EQUAL(2, kvlist_length(list));
    free(removed);

    PGTEST_FALSE(kvlist_delete(list, "key five"));
    PGTEST_TRUE(kvlist_delete(list, "key one"));
    PGTEST_EQUAL(1, kvlist_length(list));

    kvlist_destroy(list);
}

static void test_kvlist_insert_many(void)
{
    KVList list = kvlist_create();
    char key[20];
    char value[20];

    for ( size_t i = 0; i < 1000; ++i ) {
        sprintf(key, "key %zu", i + 1);
        sprintf(value, "value %zu", i + 1);
        kvlist_insert(list, key, value);
    }

    PGTEST_EQUAL(1000, kvlist_length(list));

    kvlist_destroy(list);
}

