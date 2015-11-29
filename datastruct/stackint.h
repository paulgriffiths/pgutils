#ifndef PGUTILS_STACKINT_H
#define PGUTILS_STACKINT_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stackint * StackInt;

StackInt stackint_create(void);
void stackint_destroy(StackInt stack);
size_t stackint_size(StackInt stack);
bool stackint_is_empty(StackInt stack);
void stackint_push(StackInt stack, const int n);
int stackint_pop(StackInt stack);
int stackint_peek(StackInt stack);

#endif      /*  PGUTILS_STACKINT_H  */
