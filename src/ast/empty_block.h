#ifndef EMPTY_BLOCK_H
#define EMPTY_BLOCK_H

#include "ast.h"

typedef struct {
  AstNodeType t;
} EmptyBlockNode;

AstNode* new_EmptyBlockNode();

CompileResult compile_EmptyBlock();

#endif
