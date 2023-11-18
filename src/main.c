#define _GNU_SOURCE
#include <stdio.h>

#include "ast/ast.h"
#include "parsing/parser.h"
#include "parsing/tokens.h"

CompileResult compile(char* source) {
  TokenList* tokens = TokenList_tokenise(source);
  TokenList_print(tokens);

  AstNode* ast = parse(tokens);
  CompileResult res = AstNode_compile(ast);
  AstNode_free(ast);
  return res;
}

int main() {
  char* source = readFileToString((char*) "src/main.c");
  CompileResult result = compile(source);
  printf("'%s\n'", result.assembly);
  CompileResult_free(result);
  return 0;
}
