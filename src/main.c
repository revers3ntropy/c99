#include <stdlib.h>

#include "ds/list.h"
#include "lexer.h"

int main() {
  char *processed = processFile("src/main.c");
  list_t *tokens = tokenise(processed);
  printTokenList(tokens);
  list_tokens_Free(tokens);
  free(processed);
  return 0;
}
