#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "../helpers.h"
#include "empty_block.h"

AstNode* EmptyBlockNode_new() {
  EmptyBlockNode* self = malloc(sizeof(EmptyBlockNode));
  self->t = EMPTY_BLOCK;
  return (AstNode*) self;
}

CompileResult EmptyBlock_compile(EmptyBlockNode* node) {
  UNUSED_PARAM(node);
  char* res_asm;
  asprintf(&res_asm, "nop");
  return (CompileResult){res_asm};
}

void EmptyBlock_free(EmptyBlockNode* node) {
  free(node);
}
