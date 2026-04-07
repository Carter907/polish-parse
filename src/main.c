#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "polish.h"
#include "prompt.h"

void interpret() {

  char *ln = NULL;

  size_t buff_cap = ARGS_BUFF_SIZE;
  [[maybe_unused]] size_t input_size = 0;

  char **input_split = malloc(sizeof(char *) * buff_cap);

  if (input_split == NULL) {
    perror("malloc()");
    exit(EXIT_FAILURE);
  }

  while (true) {

    printf("%s ", SHELL_PROMPT_STR);
    ssize_t rt = read_line(&ln);

    if (rt == -1) {
      perror("readline");
      exit(EXIT_FAILURE);
    }

    input_size = (size_t)rt;

    if (strcmp(ln, "exit\n") == 0) {
      free(ln);
      exit(EXIT_SUCCESS);
    }

    int result = parse_rev_polish(ln, input_size);

    printf("%d\n", result);

    free(ln);
    ln = NULL;
    free(input_split);
    input_split = NULL;
  }
}

int main(int argc, char *argv[]) {

  interpret();

  return EXIT_SUCCESS;
}
