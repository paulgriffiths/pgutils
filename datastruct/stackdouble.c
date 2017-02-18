#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "stackdouble.h"

#define INITIAL_STACK_SIZE 8

struct stackdouble {
    double * data;
    size_t top;
    size_t capacity;
};

static struct stackdouble * stackdouble_allocate(void);
static double * stackdouble_data_allocate(const size_t capacity);
static double * stackdouble_data_reallocate(double * data,
                                            const size_t capacity);
static bool stackdouble_is_full(StackDouble stack);
static void stackdouble_resize_if_full(StackDouble stack);
static void stackdouble_error_if_empty(StackDouble stack, const char * msg);

StackDouble stackdouble_create(void)
{
    struct stackdouble * new_stack = stackdouble_allocate();
    new_stack->capacity = INITIAL_STACK_SIZE;
    new_stack->top = 0;
    new_stack->data = stackdouble_data_allocate(new_stack->capacity);
    return new_stack;
}

void stackdouble_destroy(StackDouble stack)
{
    free(stack->data);
    free(stack);
}

size_t stackdouble_size(StackDouble stack)
{
    return stack->top;
}

size_t stackdouble_capacity(StackDouble stack)
{
    return stack->capacity;
}

bool stackdouble_is_empty(StackDouble stack)
{
    return stack->top == 0;
}

static bool stackdouble_is_full(StackDouble stack)
{
    return stack->top == stack->capacity;
}

static void stackdouble_resize_if_full(StackDouble stack)
{
    if ( stackdouble_is_full(stack) ) {
        stack->capacity *= 2;
        stack->data = stackdouble_data_reallocate(stack->data, stack->capacity);
    }
}

void stackdouble_push(StackDouble stack, const double n)
{
    stackdouble_resize_if_full(stack);
    stack->data[stack->top++] = n;
}

double stackdouble_pop(StackDouble stack)
{
    stackdouble_error_if_empty(stack, "couldn't pop value");
    return stack->data[--stack->top];
}

double stackdouble_peek(StackDouble stack)
{
    stackdouble_error_if_empty(stack, "couldn't peek at value");
    return stack->data[stack->top - 1];
}

static struct stackdouble * stackdouble_allocate(void)
{
    struct stackdouble * new_stack = malloc(sizeof *new_stack);
    if ( !new_stack ) {
        fprintf(stderr, "Error: couldn't create stack: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_stack;
}

static double * stackdouble_data_allocate(const size_t capacity)
{
    double * new_data = malloc(capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't create stack data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static double * stackdouble_data_reallocate(double * data,
                                            const size_t capacity)
{
    double * new_data = realloc(data, capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't resize stack data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static void stackdouble_error_if_empty(StackDouble stack, const char * msg)
{
    if ( stackdouble_is_empty(stack) ) {
        fprintf(stderr, "Error: %s: %s, line %d\n    stack is empty\n",
                msg, __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    } 
}
