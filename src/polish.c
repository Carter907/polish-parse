#include "polish.h"
#include <stdio.h>
#include <stdlib.h>

int parse_rev_polish(char *input, size_t in_size) {

  int *values = malloc(sizeof(int) * TOKEN_INITIAL_CAP);
  int top = 0;

  for (size_t i = 0; i < in_size; i++) {
    int op1, op2;
    switch (input[i]) {
    case '+':
      op1 = values[top - 1];
      op2 = values[top - 2];

      values[top - 2] = op1 + op2;
      top -= 1;

      break;

    case '-':
      op1 = values[top - 1];
      op2 = values[top - 2];

      values[top - 2] = op1 - op2;
      top -= 1;

      break;

    case ' ':
      // ignore spaces

      break;
    default:
      // must be a number
      if (isdigit(input[i])) {
        int num = (int)(input[i] - '0'); // parse digit

        values[top] = num;
        top++;
      } else if (isspace(input[i])) {

      } else {
        fprintf(stderr, "failure to parse token\n");
        exit(EXIT_FAILURE);
      }
      break;
    };
  }
  return values[top - 1];
}
