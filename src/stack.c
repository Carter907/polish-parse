#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack_t *stack_create() {
  stack_t *stk_ptr = malloc(sizeof(stack_t));
  if (stk_ptr == NULL) {
    fprintf(stderr, "failed to create stack\n");
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  stk_ptr->top = 0;
  stk_ptr->cap = INITIAL_STACK_CAP;
  stk_ptr->values = malloc(sizeof(int) * INITIAL_STACK_CAP);
  if (stk_ptr->values == NULL) {
    fprintf(stderr, "failed to create stack values\n");
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  return stk_ptr;
}

int stack_pop(stack_t *stk_ptr) {
  if (stk_ptr->top == 0) {
    fprintf(stderr, "stack_pop on empty stack\n");
    exit(EXIT_FAILURE);
  }
  int top_val = stk_ptr->values[stk_ptr->top - 1];
  stk_ptr->top--;

  return top_val;
}

void stack_push(stack_t *stk_ptr, int val) {
  if (stk_ptr->top == stk_ptr->cap - 1) {
    // double capacity
    stk_ptr->cap *= 2;
    stk_ptr->values = realloc(stk_ptr->values, stk_ptr->cap);
    if (stk_ptr->values == NULL) {
      fprintf(stderr, "failed to push to stack\n");
      perror("realloc");
      exit(EXIT_FAILURE);
    }
  }

  stk_ptr->values[stk_ptr->top] = val;
  stk_ptr->top++;
}

void stack_destroy(stack_t *stk_ptr) {
  free(stk_ptr->values);
  free(stk_ptr);
}
