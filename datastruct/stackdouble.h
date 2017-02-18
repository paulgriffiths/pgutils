#ifndef PGUTILS_STACKDOUBLE_H
#define PGUTILS_STACKDOUBLE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stackdouble * StackDouble;

StackDouble stackdouble_create(void);
void stackdouble_destroy(StackDouble stack);
size_t stackdouble_size(StackDouble stack);
bool stackdouble_is_empty(StackDouble stack);
void stackdouble_push(StackDouble stack, const double n);
double stackdouble_pop(StackDouble stack);
double stackdouble_peek(StackDouble stack);

#endif      /*  PGUTILS_STACKDOUBLE_H  */
