/*!
 * \file            string_general.h
 * \brief           Interface to string helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PGUTILS_STRING_GENERAL_H
#define PGUTILS_STRING_GENERAL_H

/*!
 * \brief           Trims CR and LF characters from the end of a string.
 * \ingroup         strings
 * \param str       The string to trim.
 * \returns         A pointer to the passed string.
 */
char *
trim_line_ending(char * str);

/*!
 * \brief           Trims trailing whitespace from a string.
 * \ingroup         strings
 * \param str       The string to trim.
 * \returns         A pointer to the passed string.
 */
char *
trim_right(char * str);

/*!
 * \brief           Trims leading whitespace from a string.
 * \ingroup         strings
 * \param str       The string to trim.
 * \returns         A pointer to the passed string.
 */
char *
trim_left(char * str);

/*!
 * \brief           Trims leading and trailing whitespace from a string
 * \ingroup         strings
 * \param str       The string to trim.
 * \returns         A pointer to the passed string.
 */
char *
trim(char * str);

/*!
 * \brief           Duplicates a string and exits on failure.
 * \ingroup         strings
 * \param str       The string to duplicate.
 * \returns         A pointer to the duplicated string.
 */
char *
term_strdup(const char * str);

#endif      /*  PGUTILS_STRING_GENERAL_H  */
