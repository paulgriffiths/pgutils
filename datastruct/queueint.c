#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "queueint.h"

#define INITIAL_QUEUE_SIZE 8

struct queueint {
    int * data;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
};

static struct queueint * queueint_allocate(void);
static int * queueint_data_allocate(const size_t capacity);
static int * queueint_data_reallocate(int * data, const size_t capacity);
static bool queueint_is_full(QueueInt queue);
static void queueint_resize_if_full(QueueInt queue);
static void queueint_error_if_empty(QueueInt queue, const char * msg);

QueueInt queueint_create(void)
{
    struct queueint * new_queue = queueint_allocate();
    new_queue->capacity = INITIAL_QUEUE_SIZE;
    new_queue->front = 0;
    new_queue->back = 0;
    new_queue->size = 0;
    new_queue->data = queueint_data_allocate(new_queue->capacity);
    return new_queue;
}

void queueint_destroy(QueueInt queue)
{
    free(queue->data);
    free(queue);
}

size_t queueint_size(QueueInt queue)
{
    return queue->size;
}

bool queueint_is_empty(QueueInt queue)
{
    return queue->size == 0;
}

static bool queueint_is_full(QueueInt queue)
{
    return queue->size == queue->capacity;
}

static void queueint_resize_if_full(QueueInt queue)
{
    if ( queueint_is_full(queue) ) {
        const size_t old_capacity = queue->capacity;
        queue->capacity *= 2;
        queue->data = queueint_data_reallocate(queue->data, queue->capacity);

        if ( queue->front > queue->back ) {
            int * old_front = queue->data + queue->front;
            int * new_front = old_front + old_capacity;
            const size_t mvsize = (old_capacity - queue->front) *
                                  sizeof *queue->data;
            memmove(new_front, old_front, mvsize);
            queue->front += old_capacity;
        }
    }
}

void queueint_enqueue(QueueInt queue, const int n)
{
    queueint_resize_if_full(queue);

    if ( !queueint_is_empty(queue) ) {
        queue->back = (queue->back + 1) % queue->capacity;
    }

    ++queue->size;
    queue->data[queue->back] = n;
}

int queueint_dequeue(QueueInt queue)
{
    queueint_error_if_empty(queue, "couldn't dequeue value");

    const int n = queue->data[queue->front];
    --queue->size;

    if ( !queueint_is_empty(queue) ) {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    else {
        queue->front = 0;
        queue->back = 0;
    }

    return n;
}

int queueint_peek(QueueInt queue)
{
    queueint_error_if_empty(queue, "couldn't peek at value");
    return queue->data[queue->front];
}

static struct queueint * queueint_allocate(void)
{
    struct queueint * new_queue = malloc(sizeof *new_queue);
    if ( !new_queue ) {
        fprintf(stderr, "Error: couldn't create queue: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_queue;
}

static int * queueint_data_allocate(const size_t capacity)
{
    int * new_data = malloc(capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't create queue data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static int * queueint_data_reallocate(int * data, const size_t capacity)
{
    int * new_data = realloc(data, capacity * sizeof *new_data);
    if ( !new_data ) {
        fprintf(stderr, "Error: couldn't resize queue data: "
                "%s, line %d\n    %s (%d)\n",
                __FILE__, __LINE__, strerror(errno), errno);
        exit(EXIT_FAILURE);
    }
    return new_data;
}

static void queueint_error_if_empty(QueueInt queue, const char * msg)
{
    if ( queueint_is_empty(queue) ) {
        fprintf(stderr, "Error: %s: %s, line %d\n    queue is empty\n",
                msg, __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}
