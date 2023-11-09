#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #include "ds/ast.h"
#include "ds/token_list.h"

#include "lexer.h"

int main() {
  char *processed = processFile((char *)"../bin/test");

  /*
    // ast testing with dodgy macro things
    AST *term =
        AST_NEW(AST_ADD, AST_NEW(AST_INTEGER, 4),
                AST_NEW(AST_ADD,
                        AST_NEW(AST_MULTIPLY, AST_NEW(AST_INTEGER, 2),
                                AST_NEW(AST_INTEGER, 10), ),
                        AST_NEW(AST_MULTIPLY, AST_NEW(AST_INTEGER, 3),
                                AST_NEW(AST_ADD, AST_NEW(AST_INTEGER, 5),
                                        AST_NEW(AST_INTEGER, 1), ), ), ), );
      ast_print(term);
  */

  // testing of parsing
  list_t *list = tokenlist_Initialise();
  scanToken(processed, list);
  tokenlist_Print(list);
  tokenlist_Free(list);

  return 0;
}
