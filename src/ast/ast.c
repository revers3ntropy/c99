#include "ast.h"
#include "empty_block.h"
#include "function_def.h"

CompileResult compileAst(AstNode *node) {
  CompileResult res;
  switch (node->type) {
    case FUNCTION_DEF:
      res = compile_FunctionDef((FunctionDefNode *) node);
      break;
    case EMPTY_BLOCK:
      res = compile_EmptyBlock();
      break;
    default:
      res = (CompileResult){(char *) "nop\n"};
  }
  free(node);
  return res;
}

void freeAstResult(CompileResult result) {
  if (result.assembly) {
    free(result.assembly);
  }
}
