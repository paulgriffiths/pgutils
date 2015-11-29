#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "stackint.h"

#define INITIAL_STACK_SIZE 8

struct stackint {
    int * data;
    size_t top;
    size_t capacity;
};

static struct stackint * stackint_allocate(void);
static int * stackint_data_allocate(const size_t capacity);
static int * stackint_data_reallocate(int * data, const size_t capacity);
static bool stackint_is_full(StackInt stack);
static void stackint_resize_if_full(StackInt stack);
static void stackint_error_if_empty(StackInt stack, const char * msg);

StackInt stackint_create(void)
{
    struct stackint * new_stack = stackint_allocate();
    new_stack->capacity = INITIAL_STACK_SIZE;
    new_stack->top = 0;
    new_stack->data = stackint_data_allocate(new_stack->capacity);
    return new_stack;
}

void stackint_destroy(StackInt stack)
{
    free(stack->data);
    free(stack);
}

size_t stackint_size(StackInt stack)
{
    return stack->top;
}

size_t stackint_capacity(StackInt stack)
{
    return stack->capacity;
}

bool stackint_is_empty(StackInt stack)
{
    return stack->top == 0;
}

static bool stackint_is_full(StackInt stack)
{
    return stack->top == stack->capacity;
}

static void stackint_resize_if_full(StackInt stack)
{
    if ( stackint_is_full(stack) ) {
        stack->capacity *= 2;
        stack->data = stackint_data_reallocate(stack->data, stack->capacity);
    }
}

void stackint_push(StackInt stack, const int n)
{
    stackint_resize_if_full(stack);
    stack->data[stack->top++] = n;
}

int stackint_pop(StackInt stack)
{
    stackint_error_if_empty(stack, "couldn't pop value");
    return stack->data[--stack->top];
}

int stackint_peek(StackInt stack)
{
    stackint_error_if_empty(stack, "couldn't peek at value");
    return stack->data[stack->top - 1];
}

static struct stackint * stackint_allocate(void)
{
    struct stackint * new_stack = malloc(sizeof *new_stack);
    if ( !new_stack ) {
        fprintf(stderr, "Error: couldn't create stack: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_stack;
}

static int * stackint_data_allocate(const size_t capacity)
{
    int * new_data = malloc(capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't create stack data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static int * stackint_data_reallocate(int * data, const size_t capacity)
{
    int * new_data = realloc(data, capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't resize stack data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static void stackint_error_if_empty(StackInt stack, const char * msg)
{
    if ( stackint_is_empty(stack) ) {
        fprintf(stderr, "Error: %s: %s, line %d\n    stack is empty\n",
                msg, __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    } 
}
