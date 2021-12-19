#ifndef ACTION_QUEUE_H
#define ACTION_QUEUE_H

#include <stdbool.h>
#include "stm32f10x.h"
#include "action.h"

#define MAXIMUM_QUEUE_LENGTH 1000

typedef struct _Queue {
    enum ActionType actions[300];
    volatile uint16_t tail;
    volatile uint16_t head;
    volatile uint16_t overflow;
} Queue;

void queue_init(Queue * q);
int queue_pop(Queue * q, enum ActionType* action);
void queue_push(Queue * q, char *action);
bool isEmpty(Queue *q);

#endif