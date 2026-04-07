#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "prompt.h"

const char *SHELL_PROMPT_STR = "polish>";

// precondition: ln must end in a '\n' character
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
// precondition: split_ln is a pointer to a pointer of char pointers
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
