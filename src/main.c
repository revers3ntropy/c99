#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ds/list.h"
#include "lexer.h"

int main() {
  const char *file = "src/main.c";
  char *processed = processFile((char *)file);
  printf("%s \n", processed);
  list_t *tokens = tokenise(processed);
  printTokenList(tokens);
  list_tokens_Free(tokens);
  free(processed);
  return 0;
}
int add(int x, int y) { return x + y; }
