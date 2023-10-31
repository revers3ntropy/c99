#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "ds/list.h"
#include "lexer.h"

int main() {
  char *processed = processFile("bin/test.c");
  free(processed);
  return 0;
}
