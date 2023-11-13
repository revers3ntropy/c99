#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"
#include "tokens.h"

AstNode *parse();// will take in list ptr to tokens

char *readFileToString(char *filename);

char *removeAllComments(char *str);

#endif
