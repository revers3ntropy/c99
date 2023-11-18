#ifndef TOKENS_H
#define TOKENS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef enum {
  // Single Character Tokens
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  SEMICOLON,
  COMMA,
  DOT,
  PLUS,
  MINUS,
  ASTERISK,
  AMPERSAND,
  PIPE,
  DOUBLE_QUOTE,
  SINGLE_QUOTE,
  LESS,
  GREATER,
  EQUAL,
  FORWARD_SLASH,
  HASH,

  // Double Character Tokens
  NOT,
  NOT_EQUAL,
  EQUAL_EQUAL,
  GREATER_EQUAL,
  LESS_EQUAL,

  // literals
  IDENTIFIER,
  STRING,
  CHARACTER,
  INTEGER,

  // keywords
  IF,
  ELSE,
  RETURN,
  INT,
  VOID,
  WHILE,
  FOR,
  INCLUDE,

  // mark eof
  EOF_TOKEN
} TokenType;

typedef struct {
  TokenType type;
  void* literal;
} Token;

typedef struct _TokenListNode {
  Token* token;
  struct _TokenListNode* next;
  struct _TokenListNode* prev;
} TokenListNode;

typedef struct {
  int size;
  TokenListNode* head;
  TokenListNode* tail;
} TokenList;

Token* Token_new(TokenType type, void* literal);

void Token_free(Token* t);

const char* TokenType_as_str(TokenType type);

void TokenList_print(TokenList* list);

TokenList* TokenList_new();

void TokenList_append(TokenList* list, Token* t);

void TokenList_remove_tail(TokenList* list);

void TokenList_free(TokenList* list);

TokenList* TokenList_tokenise(char* input);

#endif
