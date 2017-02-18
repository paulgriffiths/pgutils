#include "datastruct/stackdouble.h"
#include "testing/testing.h"

static void test_stackdouble_basic(void);
static void test_stackdouble_large(void);

int main(void)
{
    test_stackdouble_basic();
    test_stackdouble_large();
    tests_show_summary();
    return 0;
}

static void test_stackdouble_basic(void)
{
    StackDouble stack = stackdouble_create();

    PGTEST_EQUAL(0, stackdouble_size(stack));
    PGTEST_TRUE(stackdouble_is_empty(stack));

    stackdouble_push(stack, 3.0);
    PGTEST_EQUAL(1, stackdouble_size(stack));
    PGTEST_FALSE(stackdouble_is_empty(stack));
    PGTEST_EQUAL(3.0, stackdouble_peek(stack));
    PGTEST_EQUAL(1, stackdouble_size(stack));
    PGTEST_EQUAL(3.0, stackdouble_pop(stack));
    PGTEST_EQUAL(0, stackdouble_size(stack));

    stackdouble_push(stack, 4.0);
    stackdouble_push(stack, 5.0);
    stackdouble_push(stack, 6.0);

    PGTEST_EQUAL(3, stackdouble_size(stack));
    PGTEST_EQUAL(6.0, stackdouble_pop(stack));
    PGTEST_EQUAL(5.0, stackdouble_pop(stack));

    stackdouble_destroy(stack);
}

static void test_stackdouble_large(void)
{
    StackDouble stack = stackdouble_create();
    for ( double i = 1.0; i <= 1000.0; ++i ) {
        stackdouble_push(stack, i);
    }
    PGTEST_EQUAL(1000, stackdouble_size(stack));
    PGTEST_EQUAL(1000.0, stackdouble_peek(stack));

    for ( double i = 1000.0; i >= 1.0; --i ) {
        PGTEST_EQUAL(i, stackdouble_pop(stack));
    }

    PGTEST_TRUE(stackdouble_is_empty(stack));
    stackdouble_destroy(stack);
}

