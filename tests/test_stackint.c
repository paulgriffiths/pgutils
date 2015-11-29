#include "datastruct/stackint.h"
#include "testing/testing.h"

static void test_stackint_basic(void);
static void test_stackint_large(void);

int main(void)
{
    test_stackint_basic();
    test_stackint_large();
    tests_show_summary();
    return 0;
}

static void test_stackint_basic(void)
{
    StackInt stack = stackint_create();

    PGTEST_EQUAL(0, stackint_size(stack));
    PGTEST_TRUE(stackint_is_empty(stack));

    stackint_push(stack, 3);
    PGTEST_EQUAL(1, stackint_size(stack));
    PGTEST_FALSE(stackint_is_empty(stack));
    PGTEST_EQUAL(3, stackint_peek(stack));
    PGTEST_EQUAL(1, stackint_size(stack));
    PGTEST_EQUAL(3, stackint_pop(stack));
    PGTEST_EQUAL(0, stackint_size(stack));

    stackint_push(stack, 4);
    stackint_push(stack, 5);
    stackint_push(stack, 6);

    PGTEST_EQUAL(3, stackint_size(stack));
    PGTEST_EQUAL(6, stackint_pop(stack));
    PGTEST_EQUAL(5, stackint_pop(stack));

    stackint_destroy(stack);
}

static void test_stackint_large(void)
{
    StackInt stack = stackint_create();
    for ( int i = 1; i <= 1000; ++i ) {
        stackint_push(stack, i);
    }
    PGTEST_EQUAL(1000, stackint_size(stack));
    PGTEST_EQUAL(1000, stackint_peek(stack));

    for ( int i = 1000; i >= 1; --i ) {
        PGTEST_EQUAL(i, stackint_pop(stack));
    }

    PGTEST_TRUE(stackint_is_empty(stack));
    stackint_destroy(stack);
}

