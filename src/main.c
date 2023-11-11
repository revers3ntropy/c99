#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ds/token_list.h"

#include "lexer.h"

int main() {
  char *processed = processFile((char *)"./src/main.c");

  // testing of parsing
  list_t *list = tokenlist_Initialise();
  scanToken(processed, list);
  tokenlist_Print(list);
  tokenlist_Free(list);

  return 0;
}
