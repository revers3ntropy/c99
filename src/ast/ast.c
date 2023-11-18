#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "empty_block.h"
#include "function_def.h"

CompileResult AstNode_compile(AstNode* node) {
  switch (node->type) {
    case FUNCTION_DEF:
      return FunctionDef_compile((FunctionDefNode*) node);
    case EMPTY_BLOCK:
      return EmptyBlock_compile((EmptyBlockNode*) node);
    default: {
      // TODO: error handling
      char* asm_res;
      asprintf(&asm_res, "nop\n");
      return (CompileResult){asm_res};
    }
  }
}

void AstNode_free(AstNode* node) {
  switch (node->type) {
    case FUNCTION_DEF:
      FunctionDef_free((FunctionDefNode*) node);
      break;
    case EMPTY_BLOCK:
      EmptyBlock_free((EmptyBlockNode*) node);
      break;
  }
}

void CompileResult_free(CompileResult result) {
  free(result.assembly);
}
