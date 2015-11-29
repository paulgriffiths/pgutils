#include <stdlib.h>
#include "wrappers/std_wrappers.h"
#include "testing/testing.h"

int main(void) {
    char * mem = NULL;

    mem = xmalloc(100);
    PGTEST_TRUE(mem);
    mem = xrealloc(mem, 200);
    PGTEST_TRUE(mem);
    free(mem);

    mem = xcalloc(4, 1);
    PGTEST_EQUAL(0, mem[0]);
    PGTEST_EQUAL(0, mem[1]);
    PGTEST_EQUAL(0, mem[2]);
    PGTEST_EQUAL(0, mem[3]);
    free(mem);

    char * str = xstrdup("Hello, world!");
    PGTEST_STREQUAL(str, "Hello, world!");
    free(str);

    tests_show_summary();
    return 0;
}

