#ifndef STACK_H
#define STACK_H

#define INITIAL_STACK_CAP (64)

typedef struct stack_t {

	int top;
	size_t cap;	
	int *values;

} stack_t;

stack_t *stack_create();
int stack_pop(stack_t *stk_ptr);
void stack_push(stack_t *stk_ptr, int val);
void stack_destroy(stack_t *stk_ptr);

#endif
