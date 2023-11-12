#include <stdio.h>
#include <stdlib.h>

#include "function_def.h"

AstNode *new_FunctionDefNode(char *name, AstNode *body) {
  FunctionDefNode *self = malloc(sizeof(FunctionDefNode));
  self->t = FUNCTION_DEF;
  self->name = name;
  self->body = body;
  return (AstNode *) self;
}

CompileResult compile_FunctionDef(FunctionDefNode *self) {
  // get a string of the body of self and reuturn as part of res
  char *intermediate = malloc(sizeof(char) * 100);
  int used = snprintf(intermediate, 100, "%s\nreturn:\n", self->name);
  intermediate = realloc(intermediate, sizeof(char) * used + 1);
  intermediate[used] = '\0';
  CompileResult res = {
    intermediate,
  };
  return res;
}
