#include "action_queue.h"
#include "stm32f10x_rcc.h"
#include "system_stm32f10x.h"
#include "Common/utils.h"
#include "string.h"

int queue_pop(Queue * q, enum ActionType *action) {

    uint16_t tail;

    // ring buffer -> <= won't work
    if(q->tail != q->head) {
        tail = q->tail + 1;
        if(tail >= MAXIMUM_QUEUE_LENGTH) tail = 0;
        q->tail = tail;
        *action = q->actions[tail];
        return 1;
    }
    return 0;
}

void queue_push(Queue * q, char *action) {

    uint16_t head;

    head = (q->head + 1);
    if(head >= MAXIMUM_QUEUE_LENGTH) head = 0;

    enum ActionType type = ACTION_UNDEFINED;
    if (strcmp("L", action) == 0) {
      type = ACTION_L;
    } else if (strcmp("Li", action) == 0) {
      type = ACTION_LI;
    } else if (strcmp("R", action) == 0) {
      type = ACTION_R;
    } else if (strcmp("Ri", action) == 0) {
      type = ACTION_RI;
    } else if (strcmp("U", action) == 0) {
      type = ACTION_U;
    } else if (strcmp("Ui", action) == 0) {
      type = ACTION_UI;
    } else if (strcmp("D", action) == 0) {
      type = ACTION_D;
    } else if (strcmp("Di", action) == 0) {
      type = ACTION_DI;
    } else if (strcmp("F", action) == 0) {
      type = ACTION_F;
    } else if (strcmp("Fi", action) == 0) {
      type = ACTION_FI;
    } else if (strcmp("B", action) == 0) {
      type = ACTION_B;
    } else if (strcmp("Bi", action) == 0) {
      type = ACTION_BI;
    }
    
    q->actions[head] = type;
    q->head = head;

    if ( head == q->tail) {
        // skip message
        q->overflow = 1;
    }
}

bool isEmpty(Queue *q) {
	if (q->head == q->tail) return true;
	else return false;
}

void queue_init(Queue * q) {
  q->tail = 0;
  q->head = 0;
  q->overflow = 0;
}