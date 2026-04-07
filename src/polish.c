#include "polish.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int parse_rev_polish(char *input, size_t in_size) {

  stack_t *stk = stack_create();

  for (size_t i = 0; i < in_size; i++) {
    int op1, op2;
    switch (input[i]) {
    case '+':

      op2 = stack_pop(stk);
      op1 = stack_pop(stk);

      stack_push(stk, op1 + op2);

      break;

    case '-':

      op2 = stack_pop(stk);
      op1 = stack_pop(stk);

      stack_push(stk, op1 - op2);

      break;
    case '*':

      op2 = stack_pop(stk);
      op1 = stack_pop(stk);

      stack_push(stk, op1 * op2);

      break;
    case '/':

      op2 = stack_pop(stk);
      op1 = stack_pop(stk);

      stack_push(stk, op1 / op2);

      break;
    case '^':

      op2 = stack_pop(stk);
      op1 = stack_pop(stk);

      stack_push(stk, (int)pow(op1, op2));

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

      // parse number that could be multiple digits long

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
  int result = stack_pop(stk);
  stack_destroy(stk);

  return result;
}
