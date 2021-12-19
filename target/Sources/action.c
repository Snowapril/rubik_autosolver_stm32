#include "action.h"

void query_action(enum ActionType type, int *index, int *clockwise) {
  *index = ((unsigned int)type) & ACTION_TYPE_MASK;
  *clockwise = (((unsigned int)type) & ~ACTION_TYPE_MASK) == 0;
}