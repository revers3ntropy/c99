#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "lexer.h"

int main() {
  char *processed = processFile("src/lexer.h");
  free(processed);
  return 0;
}
