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

const char *tokenTypeAsString(enum tokenType type) {
  switch (type) {
  case IF:
    return "IF";
  case ELSE:
    return "ELSE";
  case RETURN:
    return "RETURN";
  case INT:
    return "INT";
  case VOID:
    return "VOID";
  case IDENTIFIER:
    return "IDENTIFIER";
  case STRING:
    return "STRING";
  case LEFT_BRACE:
    return "LEFT_BRACE";
  case RIGHT_BRACE:
    return "RIGHT_BRACE";
  case LEFT_PAREN:
    return "LEFT_PAREN";
  case RIGHT_PAREN:
    return "RIGHT_PAREN";
  case LEFT_BRACKET:
    return "LEFT_BRACKET";
  case RIGHT_BRACKET:
    return "RIGHT_BRACKET";
  case SEMICOLON:
    return "SEMICOLON";
  case COMMA:
    return "COMMA";
  case DOT:
    return "DOT";
  case PLUS:
    return "PLUS";
  case MINUS:
    return "MINUS";
  case ASTERISK:
    return "ASTERISK";
  case AMPERSAND:
    return "AMPERSAND";
  case PIPE:
    return "PIPE";
  case DOUBLE_QUOTE:
    return "DOUBLE_QUOTE";
  case SINGLE_QUOTE:
    return "SINGLE_QUOTE";
  case LESS:
    return "LESS";
  case GREATER:
    return "GREATER";
  case EQUAL:
    return "EQUAL";
  case FORWARD_SLASH:
    return "FORWARD_SLASH";
  case NOT:
    return "NOT";
  case NOT_EQUAL:
    return "NOT_EQUAL";
  case EQUAL_EQUAL:
    return "EQUAL_EQUAL";
  case GREATER_EQUAL:
    return "GREATER_EQUAL";
  case LESS_EQUAL:
    return "LESS_EQUAL";
  case INTEGER:
    return "INTEGER";
  case HASH:
    return "HASH";
  case EOF_TOKEN:
    return "EOF";
  case CHARACTER:
    return "CHAR";
  case WHILE:
    return "WHILE";
  case FOR:
    return "FOR";
      case INCLUDE:
          return "INCLUDE";
  }
  return "UNKNOWN";
}

typedef struct Token {
  enum tokenType type;
  void *literal;
} token_t;

char *token_typeToString(token_t *t) {
  uint maxlen = 256;
  char *stringRep = (char *)malloc(maxlen * sizeof(char));
  snprintf(stringRep, maxlen, "%s", tokenTypeAsString(t->type));
  stringRep = (char *)realloc(stringRep, strlen(stringRep) + 1);
  return stringRep;
}

token_t *token_new(enum tokenType type, void *literal) {
  token_t *t = (token_t *)malloc(sizeof(token_t));
  t->type = type;
  t->literal = literal;
  return t;
}
