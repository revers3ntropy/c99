#include "parser.h"
#include "../ast/empty_block.h"
#include "../ast/function_def.h"

AstNode* parse (list_t* _) {
  return new_FunctionDefNode("main", new_EmptyBlockNode());
}
