#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "function_def.h"

AstNode* FunctionDefNode_new(char* name, AstNode* body) {
  FunctionDefNode* self = malloc(sizeof(FunctionDefNode));
  self->t = FUNCTION_DEF;
  self->name = name;
  self->body = body;
  return (AstNode*) self;
}

CompileResult FunctionDef_compile(FunctionDefNode* self) {
  CompileResult bodyResult = AstNode_compile(self->body);

  char* asm_res;
  asprintf(&asm_res, "%s:\n%s\n.return:", self->name, bodyResult.assembly);
  CompileResult_free(bodyResult);
  return (CompileResult){asm_res};
}

void FunctionDef_free(FunctionDefNode* self) {
  free(self->name);
  AstNode_free(self->body);
  free(self);
}
