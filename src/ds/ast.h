#include "../lexer.h"
#include <stdlib.h>

#define AST_NEW(tag, ...)                                                      \
  ast_new((AST){tag, {.tag = (struct tag){__VA_ARGS__}}})

typedef struct AST AST;

struct AST {
  enum {
    AST_INTEGER,
    AST_ADD,
    AST_MULTIPLY,
  } tag;
  union {
    struct AST_INTEGER {
      int number;
    } AST_INTEGER;
    struct AST_ADD {
      AST *left;
      AST *right;
    } AST_ADD;
    struct AST_MULTIPLY {
      AST *left;
      AST *right;
    } AST_MULTIPLY;
  } data;
};

AST *ast_new(AST ast) {
  AST *ptr = (AST *)malloc(sizeof(AST));
  if (ptr) {
    *ptr = ast;
  }
  return ptr;
}

void ast_print(AST *ptr) {
  AST ast = *ptr;
  switch (ast.tag) {
  case AST_INTEGER: {
    printf("%d", ast.data.AST_INTEGER.number);
    return;
  }
  case AST_ADD: {
    printf("(");
    ast_print(ast.data.AST_ADD.left);
    printf(" + ");
    ast_print(ast.data.AST_ADD.right);
    printf(")");
    return;
  }
  case AST_MULTIPLY: {
    printf("(");
    ast_print(ast.data.AST_MULTIPLY.left);
    printf(" * ");
    ast_print(ast.data.AST_MULTIPLY.right);
    printf(")");
    return;
  }
  }
}
