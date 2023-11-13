#ifndef FUNCTION_DEF_H
#define FUNCTION_DEF_H

#include <stdlib.h>

#include "ast.h"

typedef struct {
  AstNodeType t;
  char* name;
  AstNode* body;
} FunctionDefNode;

AstNode* new_FunctionDefNode(char* name, AstNode* body);

CompileResult compile_FunctionDef(FunctionDefNode* self);

#endif
