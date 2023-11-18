#ifndef EMPTY_BLOCK_H
#define EMPTY_BLOCK_H

#include "ast.h"

typedef struct {
  AstNodeType t;
} EmptyBlockNode;

AstNode* EmptyBlockNode_new();
CompileResult EmptyBlock_compile(EmptyBlockNode* node);
void EmptyBlock_free(EmptyBlockNode* node);

#endif
