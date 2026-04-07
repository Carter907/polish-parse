#include "polish.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct operands_t {
  int first; // second element off the stack
  int second; // first element off the stack

} ops_t;

ops_t get_operands(stack_t *stk_ptr) {

  int op_2 = stack_pop(stk_ptr);
  int op_1 = stack_pop(stk_ptr);

  return (ops_t){ .first = op_1, .second = op_2 };
}

int parse_rev_polish(char *input, size_t in_size) {

  stack_t *stk = stack_create();

	ops_t ops = {0};

  for (size_t i = 0; i < in_size; i++) {


    switch (input[i]) {

    case '+':

			ops = get_operands(stk);

      stack_push(stk, ops.first + ops.second);

      break;

    case '-':

			ops = get_operands(stk);

      stack_push(stk, ops.first - ops.second);

      break;
    case '*':

			ops = get_operands(stk);

      stack_push(stk, ops.first * ops.second);

      break;
    case '/':

			ops = get_operands(stk);

      stack_push(stk, ops.first / ops.second);

      break;
    case '^':

			ops = get_operands(stk);

      stack_push(stk, (int)pow(ops.first, ops.second));

      break;
    case ' ':
      // ignore spaces

      break;
    default:

      char ch = input[i];

      if (isspace(ch)) { // check for space characters other than ' '
        break;
      }

      if (!isdigit(ch)) {
        stack_destroy(stk);
        free(input);
        fprintf(stderr, "failure to parse token\n");
        exit(EXIT_FAILURE);
      }

      // must be a number

      // parse number 0 or more digits long (Kleene closure of digits)

      int j = (int)i + 1;
      int num = 0;
      int num_length = 1;

      while (j < in_size) {

        ch = input[j];

        if (!isdigit(ch)) {
          break;
        }

        num_length++;
        j++;
      }

      for (j = 0; j < num_length; j++) {
        num += (input[(int)i + j] - '0') * (int)pow(10, num_length - j - 1);
      }

      stack_push(stk, num);

      i += (size_t)(num_length - 1);

      break;
    };
  }

  if (stk->top != 1) {
    stack_destroy(stk);
    fprintf(stderr, "invalid end state, check for valid notation\n");
    exit(EXIT_FAILURE);
  }

  int result = stack_pop(stk);
  stack_destroy(stk);

  return result;
}
