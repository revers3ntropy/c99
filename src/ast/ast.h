#ifndef AST_H
#define AST_H

typedef enum {
  FUNCTION_DEF,
  EMPTY_BLOCK,
} AstNodeType;

// basic form of polymorphism -
// everything which 'inherits' from AstNode must have its type
// as the first member of the struct, allowing us to cast
// to the actual type of the node as needed.
typedef struct {
  AstNodeType type;
} AstNode;

typedef struct {
  char* assembly;
} CompileResult;

CompileResult compileAst(AstNode* node);

void freeAstResult(CompileResult result);

#endif
