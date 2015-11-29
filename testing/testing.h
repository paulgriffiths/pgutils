#ifndef PGUTILS_TESTING_H
#define PGUTILS_TESTING_H

#include <stdbool.h>

enum pg_test_type {
    PGTEST_TEST,
    PGTEST_ASSERTION
};

#define PGTEST(cond) pg_test_condition(PGTEST_TEST, (cond), (#cond), \
        __func__, __FILE__, __LINE__)
#define PGTEST_TRUE(cond) pg_test_condition(PGTEST_TEST, (cond), (#cond), \
        __func__, __FILE__, __LINE__)
#define PGTEST_FALSE(cond) pg_test_condition(PGTEST_TEST, (!(cond)), \
        ("!" #cond), __func__, __FILE__, __LINE__)
#define PGTEST_STREQUAL(s1, s2) pg_test_strcmp(PGTEST_TEST, \
        (s1), (s2), __func__, __FILE__, __LINE__)
#define PGTEST_EQUAL(n1, n2) pg_test_llequal(PGTEST_TEST, \
        ((long long) n1), ((long long) n2), __func__, __FILE__, __LINE__)

#ifndef NDEBUG
#define PGASSERT(cond) pg_test_condition(PGTEST_ASSERTION, \
        (cond), (#cond), __func__, __FILE__, __LINE__)
#define PGASSERT_STREQUAL(s1, s2) pg_test_strcmp(PGTEST_ASSERTION, \
        (s1), (s2), __func__, __FILE__, __LINE__)
#define PGASSERT_EQUAL(n1, n2) pg_test_llequal(PGTEST_ASSERTION, \
        ((long long) n1), ((long long) n2), __func__, __FILE__, __LINE__)
#else
#define PGASSERT(cond)
#define PGASSERT_STREQUAL(s1, s2)
#define PGASSERT_EQUAL(n1, n2)
#endif

#ifdef DEBUG
#define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
#else
#define DPRINTF(...)
#endif

#ifdef DEBUG
#define DPRINTFLINE(...) fprintf(stderr, "[%s, line %d]: ", \
        __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define DPRINTFLINE(...)
#endif

#define QUIT_STRERROR(...) pgutils_exit_strerror(__FILE__, \
        __LINE__, (errno), __VA_ARGS__)
#define QUIT_ERROR(...) pgutils_exit_error(__FILE__, \
        __LINE__, __VA_ARGS__)

void pg_test_condition(const enum pg_test_type type, const bool cond,
                       const char * msg, const char * fnc,
                       const char * file, const int line);
void pg_test_strcmp(const enum pg_test_type type,
                    const char * s1, const char * s2, const char * fnc,
                    const char * file, const int line);
void pg_test_llequal(const enum pg_test_type type,
                     const long long n1, const long long n2, const char * fnc,
                     const char * file, const int line);
void tests_show_summary(void);

void pgutils_exit_strerror(const char * file, const int line,
                           const int errnum, const char * fmt, ...);
void pgutils_exit_error(const char * file, const int line,
                        const char * fmt, ...);

#endif      /*  PGUTILS_TESTING_H  */
