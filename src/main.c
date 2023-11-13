#include <stdio.h>
#include <stdlib.h>

#include "ast/ast.h"
#include "parsing/parser.h"
#include "parsing/tokens.h"

void compile(char* source) {
  list_t* tokens = tokenise(source);

  tokenlist_Print(tokens);
  AstNode* ast = parse(tokens);
  tokenlist_Free(tokens);

  CompileResult result = compileAst(ast);
  printf("%s\n", result.assembly);
  freeAstResult(result);
}

int main() {
  char* source = readFileToString((char*) "src/main.c");
  compile(source);
  free(source);
  return 0;
}
