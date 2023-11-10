#include <stdlib.h>

#include "function_def.h"

AstNode* new_FunctionDefNode(char* name, AstNode* body) {
  FunctionDefNode* self = malloc(sizeof(FunctionDefNode));
  self->t = FUNCTION_DEF;
  self->name = name;
  self->body = body;
  return (AstNode*)self;
}

CompileResult compile_FunctionDef(FunctionDefNode *self) {
  CompileResult res = {
    "something:\nret\n"
  };
  return res;
}
