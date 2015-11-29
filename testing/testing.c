#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "testing.h"

static int num_tests = 0;
static int num_passed = 0;
static int num_failed = 0;

static void pg_test_add_passed_test(void);
static void pg_test_add_failed_test(void);
static char * pg_test_type_name(const enum pg_test_type type);

void pg_test_condition(const enum pg_test_type type, const bool cond,
                       const char * msg, const char * fnc,
                       const char * file, const int line)
{
    if ( cond ) {
        if ( type == PGTEST_TEST ) {
            pg_test_add_passed_test();
        }
    }
    else {
        fprintf(stderr, "%s failed: %s() (%s line %d)\n"
                "    %s is NOT true\n",
                pg_test_type_name(type), fnc, file, line, msg);

        if ( type == PGTEST_TEST ) {
            pg_test_add_failed_test();
        }
        else if ( type == PGTEST_ASSERTION ) {
            fflush(stderr);
            abort();
        }
    }
}

void pg_test_strcmp(const enum pg_test_type type,
                    const char * s1, const char * s2, const char * fnc,
                    const char * file, const int line)
{
    if ( !strcmp(s1, s2) ) {
        if ( type == PGTEST_TEST ) {
            pg_test_add_passed_test();
        }
    }
    else {
        fprintf(stderr, "%s failed: %s() (%s, line %d)\n"
                "    \"%s\" != \"%s\"\n",
                pg_test_type_name(type), fnc, file, line, s1, s2);

        if ( type == PGTEST_TEST ) {
            pg_test_add_failed_test();
        }
        else if ( type == PGTEST_ASSERTION ) {
            fflush(stderr);
            abort();
        }
    }
}

void pg_test_llequal(const enum pg_test_type type,
                     const long long n1, const long long n2, const char * fnc,
                     const char * file, const int line)
{
    if ( n1 == n2 ) {
        if ( type == PGTEST_TEST ) {
            pg_test_add_passed_test();
        }
    }
    else {
        fprintf(stderr, "%s failed: %s() (%s, line %d)\n"
                "    %lld != %lld\n",
                pg_test_type_name(type), fnc, file, line, n1, n2);

        if ( type == PGTEST_TEST ) {
            pg_test_add_failed_test();
        }
        else if ( type == PGTEST_ASSERTION ) {
            fflush(stderr);
            abort();
        }
    }
}

void tests_show_summary(void)
{
    if ( num_tests > 0 ) {
        fprintf(stderr, "Out of %d tests, %d passed and %d failed "
                "(%2.1f%% success).\n", num_tests, num_passed, num_failed,
                num_passed * 100.0 / num_tests);
    }
    else {
        fprintf(stderr, "No tests were ran.\n");
    }
}

static void pg_test_add_passed_test(void)
{
    ++num_tests;
    ++num_passed;
}

static void pg_test_add_failed_test(void)
{
    ++num_tests;
    ++num_failed;
}

static char * pg_test_type_name(const enum pg_test_type type)
{
    switch ( type ) {
        case PGTEST_TEST:
            return "Test";

        case PGTEST_ASSERTION:
            return "Assertion";

        default:
            fprintf(stderr, "Unrecognized test type!\n");
            abort();
    }
}

void pgutils_exit_strerror(const char * file, const int line,
                           const int errnum, const char * fmt, ...)
{
    fprintf(stderr, "Error: ");

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fprintf(stderr, ": %s (%d): %s, line %d\n",
            strerror(errnum), errnum, file, line);

    exit(EXIT_FAILURE);
}

void pgutils_exit_error(const char * file, const int line,
                        const char * fmt, ...)
{
    fprintf(stderr, "Error: ");

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fprintf(stderr, ": %s, line %d\n", file, line);

    exit(EXIT_FAILURE);
}

