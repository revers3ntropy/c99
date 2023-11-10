#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"
#include "../ds/list.h"

AstNode* parse (list_t* tokens);

#endif
