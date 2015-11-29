#include "datastruct/queueint.h"
#include "testing/testing.h"

static void test_queueint_basic(void);
static void test_queueint_large(void);
static void test_queueint_large_crossover(void);

int main(void)
{
    test_queueint_basic();
    test_queueint_large();
    test_queueint_large_crossover();
    tests_show_summary();
    return 0;
}

static void test_queueint_basic(void)
{
    QueueInt queue = queueint_create();

    PGTEST_EQUAL(0, queueint_size(queue));
    PGTEST_TRUE(queueint_is_empty(queue));

    queueint_enqueue(queue, 3);
    PGTEST_EQUAL(1, queueint_size(queue));
    PGTEST_FALSE(queueint_is_empty(queue));
    PGTEST_EQUAL(3, queueint_peek(queue));
    PGTEST_EQUAL(1, queueint_size(queue));
    PGTEST_EQUAL(3, queueint_dequeue(queue));
    PGTEST_EQUAL(0, queueint_size(queue));

    queueint_enqueue(queue, 4);
    queueint_enqueue(queue, 5);
    queueint_enqueue(queue, 6);

    PGTEST_EQUAL(3, queueint_size(queue));
    PGTEST_EQUAL(4, queueint_dequeue(queue));
    PGTEST_EQUAL(5, queueint_dequeue(queue));

    queueint_destroy(queue);
}

static void test_queueint_large(void)
{
    QueueInt queue = queueint_create();
    for ( int i = 1; i <= 1000; ++i ) {
        queueint_enqueue(queue, i);
    }
    PGTEST_EQUAL(1000, queueint_size(queue));
    PGTEST_EQUAL(1, queueint_peek(queue));

    for ( int i = 1; i <= 1000; ++i ) {
        PGTEST_EQUAL(i, queueint_dequeue(queue));
    }

    PGTEST_TRUE(queueint_is_empty(queue));
    queueint_destroy(queue);
}

static void test_queueint_large_crossover(void)
{
    QueueInt queue = queueint_create();

    for ( int i = 1; i <= 192; ++i ) {
        queueint_enqueue(queue, i);
    }

    for ( int i = 1; i <= 192; ++i ) {
        queueint_enqueue(queue, i);
    }

    PGTEST_EQUAL(384, queueint_size(queue));

    for ( int i = 1; i <= 192; ++i ) {
        PGTEST_EQUAL(i, queueint_dequeue(queue));
    }

    PGTEST_EQUAL(192, queueint_size(queue));
    PGTEST_EQUAL(1, queueint_peek(queue));

    for ( int i = 193; i <= 1000; ++i ) {
        queueint_enqueue(queue, i);
    }

    PGTEST_EQUAL(1000, queueint_size(queue));
    PGTEST_EQUAL(1, queueint_peek(queue));

    for ( int i = 1; i <= 1000; ++i ) {
        PGTEST_EQUAL(i, queueint_dequeue(queue));
    }

    PGTEST_EQUAL(0, queueint_size(queue));
    PGTEST_TRUE(queueint_is_empty(queue));

    queueint_destroy(queue);
}
