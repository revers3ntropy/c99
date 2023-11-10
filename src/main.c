#include <stdlib.h>

#include "ds/list.h"
#include "parse/lexer.h"
#include "parse/parser.h"

void compile(char* source) {
  list_t* tokens = tokenise(source);
  free(source);

  printTokenList(tokens);
  AstNode* ast = parse(tokens);
  list_tokens_Free(tokens);

  CompileResult result = compileAst(ast);
  printf("%s\n", result.assembly);
}

int main() {
  char* source = readFileToString("src/main.c");
  compile(source);
  return 0;
}
