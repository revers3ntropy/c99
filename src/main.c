#include <stdlib.h>

#include "ds/list.h"
#include "lexer.h"

void compile(char *source) {
  list_t *tokens = tokenise(source);
  printTokenList(tokens);
  list_tokens_Free(tokens);
  free(source);
}

int main() {
  char *source = readFileToString("src/main.c");
  compile(source);
  return 0;
}
