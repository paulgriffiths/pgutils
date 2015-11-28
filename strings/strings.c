#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strings.h"


char * trim_trailing_newline(char * str)
{
    const size_t length = strlen(str);
    if ( length > 0 && str[length - 1] == '\n' ) {
        str[length - 1] = '\0';
    }
    return str;
}


char * trim_right(char * str)
{
    if ( str[0] != '\0' ) {
        for ( int last = ((int) strlen(str)) - 1;
              last >= 0 && isspace(str[last]);
              --last ) {
            str[last] = '\0';
        }
    }

    return str;
}


char * trim_left(char * str)
{
    const size_t length = strlen(str);

    if ( length > 0 ) {
        size_t leading = 0;

        while ( str[leading] != '\0' && isspace(str[leading]) ) {
            ++leading;
        }

        if ( leading > 0 ) {
            memmove(str, str + leading, length - leading + 1);
        }
    }

    return str;
}


char * trim(char * str)
{
    trim_left(str);
    trim_right(str);
    return str;
}
