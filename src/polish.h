#ifndef _POLISH_H
#define _POLISH_H

#include <ctype.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

#define TOKEN_INITIAL_CAP (64)

typedef enum {
  ADD,
  SUBTRACT,
  SPACE,
} token_char_e;

extern char token_chars[3];

typedef union {
  token_char_e tok;
  int number;
} valid_token_t;

int parse_rev_polish(char *input, size_t in_size);

#endif
