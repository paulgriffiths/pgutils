#ifndef PGUTILS_QUEUEINT_H
#define PGUTILS_QUEUEINT_H

#include <stddef.h>
#include <stdbool.h>

typedef struct queueint * QueueInt;

QueueInt queueint_create(void);
void queueint_destroy(QueueInt queue);
size_t queueint_size(QueueInt queue);
bool queueint_is_empty(QueueInt queue);
void queueint_enqueue(QueueInt queue, const int n);
int queueint_dequeue(QueueInt queue);
int queueint_peek(QueueInt queue);

#endif      /*  PGUTILS_QUEUEINT_H  */
