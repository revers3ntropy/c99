#ifndef FUNCTION_DEF_H
#define FUNCTION_DEF_H

#include <stdlib.h>

#include "ast.h"

typedef struct {
  AstNodeType t;
  char* name;
  AstNode* body;
} FunctionDefNode;

AstNode* FunctionDefNode_new(char* name, AstNode* body);
CompileResult FunctionDef_compile(FunctionDefNode* self);
void FunctionDef_free(FunctionDefNode* self);

#endif
