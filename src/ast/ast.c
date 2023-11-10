#include "ast.h"
#include "empty_block.h"
#include "function_def.h"

CompileResult compileAst(AstNode* node) {
  switch (node->type) {
    case FUNCTION_DEF: return compile_FunctionDef((FunctionDefNode*)node);
    case EMPTY_BLOCK: return compile_EmptyBlock((EmptyBlockNode*)node);
  }
  return (CompileResult){ "nop\n" };
}
