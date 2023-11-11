#ifndef TOKENS_H
#define TOKENS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

enum tokenType {
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
};

typedef struct Token {
  enum tokenType type;
  void *literal;
} token_t;

typedef struct listNode {
  token_t *token;
  struct listNode *next;
  struct listNode *prev;
} listNode_t;

typedef struct listContainer {
  int size;
  struct listNode *head;
  struct listNode *tail;
} list_t;

token_t *token_new(enum tokenType type, void *literal);

const char *tokenTypeAsString(enum tokenType type);

void tokenlist_Print(list_t *list);

list_t *tokenlist_Initialise();

void tokenlist_Append(list_t *list, token_t *t);

void tokenlist_RemoveTail(list_t *list);

void tokenlist_Free(list_t *list);

void scanToken(char *input, list_t *list);

#endif