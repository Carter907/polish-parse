#ifndef PROMPT_H
#define PROMPT_H

#include <stddef.h>

#define ARGS_BUFF_SIZE (256)
#define DELIM_WHITESPACE (" \t\r\n")

#define LINE_BUFF_SIZE (64)

extern const char *SHELL_PROMPT_STR;

ssize_t read_line(char **ln);
size_t split_line(char ***split_ln, size_t *split_ln_sz, char *ln);

#endif
