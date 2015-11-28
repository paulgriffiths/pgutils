#define DEBUG
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "strings/strings.h"
#include "testing/testing.h"

static void test_strings(void);
static void test_trim_right(void);
static void test_trim_left(void);
static void test_trim(void);
static void test_trim_trailing_newline(void);

int main(void)
{
    test_strings();
    tests_show_summary();
    return 0;
}

void test_strings(void)
{
    test_trim_right();
    test_trim_left();
    test_trim();
    test_trim_trailing_newline();
}

void test_trim_right(void)
{
    char buffer[100] = "a string \r\n\t  ";

    trim_right(buffer);
    PGTEST_STREQUAL(buffer, "a string");

    strcpy(buffer, " a string \r\n\t  ");
    trim_right(buffer);
    PGTEST_STREQUAL(buffer, " a string");

    strcpy(buffer, "");
    trim_right(buffer);
    PGTEST_STREQUAL(buffer, "");
}

void test_trim_left(void)
{
    char buffer[100] = " \r\n\t  a string";

    trim_left(buffer);
    PGTEST_STREQUAL(buffer, "a string");

    strcpy(buffer, " \r\n\t  a string  ");
    trim_left(buffer);
    PGTEST_STREQUAL(buffer, "a string  ");

    strcpy(buffer, "");
    trim_left(buffer);
    PGTEST_STREQUAL(buffer, "");
}

void test_trim(void)
{
    char buffer[100] = " \r\n\t  a string \t\n\r   ";

    trim(buffer);
    PGTEST_STREQUAL(buffer, "a string");

    strcpy(buffer, "a string");
    trim(buffer);
    PGTEST_STREQUAL(buffer, "a string");

    strcpy(buffer, "");
    trim(buffer);
    PGTEST_STREQUAL(buffer, "");
}

void test_trim_trailing_newline(void)
{
    char buffer[100] = "a string \n";

    trim_trailing_newline(buffer);
    PGTEST_STREQUAL(buffer, "a string ");

    strcpy(buffer, "a string ");
    trim_trailing_newline(buffer);
    PGTEST_STREQUAL(buffer, "a string ");
}
