#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "function_def.h"

AstNode* new_FunctionDefNode(char* name, AstNode* body) {
  FunctionDefNode* self = malloc(sizeof(FunctionDefNode));
  self->t = FUNCTION_DEF;
  self->name = name;
  self->body = body;
  return (AstNode*) self;
}

CompileResult compile_FunctionDef(FunctionDefNode* self) {
  CompileResult bodyResult = compileAst(self->body);

  char* asm_res;
  asprintf(&asm_res, "%s:\n%s\n.return:\n", self->name, bodyResult.assembly);
  return (CompileResult) { asm_res };
}
