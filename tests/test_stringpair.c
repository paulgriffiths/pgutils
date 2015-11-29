#include "strings/strings.h"
#include "datastruct/stringpair.h"
#include "testing/testing.h"

int main(void)
{
    StringPair pair = stringpair_create("string one", "string two");
    PGTEST_STREQUAL("string one", stringpair_first(pair));
    PGTEST_STREQUAL("string two", stringpair_second(pair));
    stringpair_destroy(pair);

    char * s1 = dup_string("string three");
    char * s2 = dup_string("string four");
    pair = stringpair_create_allocated(s1, s2);
    PGTEST_STREQUAL("string three", stringpair_first(pair));
    PGTEST_STREQUAL("string four", stringpair_second(pair));
    stringpair_destroy(pair);

    tests_show_summary();
    return 0;
}
