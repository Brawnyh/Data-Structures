#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define QueueSize 16
typedef struct s_Queue Queue;


Queue* createQueue(void);
Queue * queue_push(Queue *q,int val);
int queue_top(const Queue *q);
bool queue_empty(const Queue *q);
bool queue_size(const Queue *q);

#endif










#endif