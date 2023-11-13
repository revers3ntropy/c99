#ifndef LEXER_H
#define LEXER_H

#include "../ds/list.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tokenTypes {
  ADDITION = '+',
  SUBTRACTION = '-',
  ASTERISK = '*',
  DIVISION = '/',
  ADRRESS_OF = '&',
  LEFT_BRACE = '{',
  RIGHT_BRACE = '}',
  LEFT_PAREN = '(',
  RIGHT_PAREN = ')',
  SEMICOLON = ';',
  HASH = '#',
  EQUALS = '=',
  LEFT_CROCODILE = '<',
  RIGHT_CROCODILE = '>',
  LEFT_SQUARE_BRACKET = '[',
  RIGHT_SQUARE_BRACKET = ']',
  IDENTIFIER = 'i',
  CHAR_LITERAL = 'c',
  STRING_LITERAL = 's',
  INTEGER_LITERAL = 'd',
} tokenType;

typedef struct token {
  void* value;
  tokenType type;
} token_t;

void printTokenList(list_t* list);

void list_tokens_Free(list_t* list);

token_t* newToken(void* value, tokenType type);

char* readFileToString(char* filename);

char* removeAllComments(char* str);

list_t* tokenise(char* source_code);

#endif
