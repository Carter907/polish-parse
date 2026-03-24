#define _XOPEN_SOURCE 700

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "polish.h"

#define ARGS_BUFF_SIZE (256)
#define DELIM_WHITESPACE (" \t\r\n")

#define LINE_BUFF_SIZE (64)

const char *SHELL_PROMPT_STR = "rev_polish>";

ssize_t read_line(char **ln) {

  ssize_t ln_sz = 0;
  size_t buff_cap = LINE_BUFF_SIZE;

  *ln = malloc(sizeof(char) * LINE_BUFF_SIZE);

  int next_char;

  while ((next_char = getchar()) != EOF) {

    char ch = (char)next_char;
    (*ln)[ln_sz++] = ch;

    if (ln_sz == buff_cap) {
      buff_cap *= 2;
      *ln = realloc(*ln, sizeof(char) * buff_cap);
    };

    if (next_char == '\n')
      break;
  };

  if (feof(stdin)) {
    free(*ln);
    return -1;
  }

  (*ln)[ln_sz] = '\0';

  return ln_sz;
}

size_t split_line(char ***split_ln, size_t *split_ln_sz, char *ln) {

  if (*split_ln == nullptr) {
    *split_ln = malloc(sizeof(char *) * ARGS_BUFF_SIZE);
  }

  size_t pos = 0;
  char *tok = strtok(ln, DELIM_WHITESPACE);

  do {

    (*split_ln)[pos] = tok;
    pos++;

    if (pos == *split_ln_sz) {

      (*split_ln_sz) *= 2;
      *split_ln = realloc(*split_ln, sizeof(char *) * (*split_ln_sz));

      if (*split_ln == nullptr) {
        perror("realloc()");
        exit(EXIT_FAILURE);
      }
    }

    tok = strtok(nullptr, DELIM_WHITESPACE);

  } while (tok != nullptr);

  (*split_ln)[pos] = (char *)NULL;

  return pos;
}

int interpret() {

  char *ln = nullptr;

  size_t buff_cap = ARGS_BUFF_SIZE;
  [[maybe_unused]] size_t input_size = 0;

  char **input_split = malloc(sizeof(char *) * buff_cap);

  if (input_split == nullptr) {
    perror("malloc()");
    exit(EXIT_FAILURE);
  }

  while (true) {

    printf("%s ", SHELL_PROMPT_STR);
    ssize_t rt = read_line(&ln);

    if (rt == -1) {
      perror("readline()");
      exit(EXIT_FAILURE);
    }

    input_size = (size_t)rt;

    int result = parse_rev_polish(ln, input_size);
    printf("%d\n", result);

    free(ln);
    ln = nullptr;
    free(input_split);
    input_split = nullptr;
  }

  return 0;
}

int main(int argc, char *argv[]) {

  interpret();

  return EXIT_SUCCESS;
}
