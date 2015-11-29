#ifndef PGUTILS_STRINGPAIR_H
#define PGUTILS_STRINGPAIR_H

typedef struct stringpair * StringPair;

StringPair stringpair_create(const char * s1, const char * s2);
StringPair stringpair_create_allocated(char * s1, char * s2);
char * stringpair_first(StringPair pair);
char * stringpair_second(StringPair pair);
void stringpair_destroy(StringPair pair);

#endif      /*  PGUTILS_STRINGPAIR_H  */
