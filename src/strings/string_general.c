/*!
 * \file            string_general.c
 * \brief           Implementation of string helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


/*!
 * \brief           Enables POSIX library functions
 */

#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_general.h"


char * trim_line_ending(char * str)
{
    if ( *str != '\0' ) {
        int last;
        for ( last = (int) strlen(str) - 1;
              last >= 0 && ( str[last] == '\n' || str[last] == '\r' );
              --last ) {
            str[last] = '\0';
        }
    }

    return str;
}


char * trim_right(char * str)
{
    if ( *str != '\0' ) {
        int last;
        for ( last = (int) strlen(str) - 1;
              last >= 0 && isspace(str[last]);
              --last ) {
            str[last] = '\0';
        }
    }

    return str;
}


char * trim_left(char * str)
{
    char * leading = str;
    char * orig_head = str;

    while ( *leading != '\0' && isspace(*leading) ) {
        ++leading;
    }

    while ( *leading != '\0' ) {
        *orig_head++ = *leading++;
    }

    return str;
}


char * trim(char * str)
{
    (void) trim_left(str);
    (void) trim_right(str);
    return str;
}


char * term_strdup(const char * str)
{
    char * new_str;

    if ( (new_str = strdup(str)) == NULL ) {
        fprintf(stderr, "Couldn't allocate memory - exiting.\n");
        exit(EXIT_FAILURE);
    }

    return new_str;
}
