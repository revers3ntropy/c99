#include <stdlib.h>

#include "empty_block.h"

AstNode* new_EmptyBlockNode() {
  EmptyBlockNode* self = malloc(sizeof(EmptyBlockNode));
  self->t = EMPTY_BLOCK;
  return (AstNode*)self;
}

CompileResult compile_EmptyBlock(EmptyBlockNode *_self) {
  CompileResult res = { "nop\n" };
  return res;
}

