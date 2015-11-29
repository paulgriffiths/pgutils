#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stringpair.h"

struct stringpair {
    char * first;
    char * second;
};

StringPair stringpair_create(const char * s1, const char * s2)
{
    struct stringpair * new_pair = malloc(sizeof *new_pair);
    if ( !new_pair ) {
        fprintf(stderr, "Error: couldn't create string pair: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    new_pair->first = malloc(strlen(s1) + 1);
    if ( !new_pair->first ) {
        fprintf(stderr, "Error: couldn't duplicate string: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    strcpy(new_pair->first, s1);

    new_pair->second = malloc(strlen(s2) + 1);
    if ( !new_pair->second ) {
        fprintf(stderr, "Error: couldn't duplicate string: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    strcpy(new_pair->second, s2);

    return new_pair;
}

StringPair stringpair_create_allocated(char * s1, char * s2)
{
    struct stringpair * new_pair = malloc(sizeof *new_pair);
    if ( !new_pair ) {
        fprintf(stderr, "Error: couldn't create string pair: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }

    new_pair->first = s1;
    new_pair->second = s2;

    return new_pair;
}

char * stringpair_first(StringPair pair)
{
    return pair->first;
}

char * stringpair_second(StringPair pair)
{
    return pair->second;
}

void stringpair_destroy(StringPair pair)
{
    free(pair->first);
    free(pair->second);
    free(pair);
}

