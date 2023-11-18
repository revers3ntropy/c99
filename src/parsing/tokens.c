#define _GNU_SOURCE
#include "tokens.h"
#include <stdio.h>

const char* TokenType_as_str(TokenType type) {
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

Token* Token_new(TokenType type, void* literal) {
  Token* t = (Token*) malloc(sizeof(Token));
  t->type = type;
  t->literal = literal;
  return t;
}

void Token_free(Token* t) {
  if (t) {
    if (t->literal) {
      free(t->literal);
    }
    free(t);
  }
}

void TokenList_print(TokenList* list) {
  TokenListNode* node = list->head;
  printf("[ ");
  while (node != NULL && node->token != NULL) {
    if (node->token->type == STRING || node->token->type == CHARACTER) {
      printf("%s(\"%s\") ", TokenType_as_str(node->token->type),
             (char*) node->token->literal);
    } else if (node->token->type == IDENTIFIER) {
      printf("%s ", (char*) node->token->literal);
    } else {
      printf("%s ", TokenType_as_str(node->token->type));
    }
    node = node->next;
  }
  printf("]\n");
}

TokenList* TokenList_new() {
  TokenList* list = (TokenList*) malloc(sizeof(TokenList));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void TokenList_append(TokenList* list, Token* t) {
  TokenListNode* newNode = (TokenListNode*) malloc(sizeof(TokenListNode));
  newNode->token = t;
  if (list->size == 0) {
    newNode->next = NULL;
    newNode->prev = NULL;
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->next = NULL;
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
  }
  list->size++;
}

// will attempt to free the token in the tail node
void TokenList_remove_tail(TokenList* list) {
  if (list->size == 0) {
    return;
  } else if (list->size == 1) {
    Token_free(list->tail->token);
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return;
  }
  TokenListNode* temp = list->tail;
  list->tail = list->tail->prev;
  list->tail->next = NULL;
  Token_free(temp->token);
  free(temp);
  list->size--;
}

void TokenList_free(TokenList* list) {
  while (list->size > 0) {
    TokenList_remove_tail(list);
  }
  free(list);
}

TokenList* TokenList_tokenise(char* input) {
  TokenList* list = TokenList_new();
  uint i = 0;
  while (i < strlen(input)) {
    switch (input[i]) {
      case '#':
        TokenList_append(list, Token_new(HASH, NULL));
        break;
      case '(':
        TokenList_append(list, Token_new(LEFT_PAREN, NULL));
        break;
      case ')':
        TokenList_append(list, Token_new(RIGHT_PAREN, NULL));
        break;
      case '[':
        TokenList_append(list, Token_new(LEFT_BRACKET, NULL));
        break;
      case ']':
        TokenList_append(list, Token_new(RIGHT_BRACKET, NULL));
        break;
      case ';':
        TokenList_append(list, Token_new(SEMICOLON, NULL));
        break;
      case ',':
        TokenList_append(list, Token_new(COMMA, NULL));
        break;
      case '.':
        TokenList_append(list, Token_new(DOT, NULL));
        break;
      case '+':
        TokenList_append(list, Token_new(PLUS, NULL));
        break;
      case '-':
        TokenList_append(list, Token_new(MINUS, NULL));
        break;
      case '*':
        TokenList_append(list, Token_new(ASTERISK, NULL));
        break;
      case '{':
        TokenList_append(list, Token_new(LEFT_BRACE, NULL));
        break;
      case '}':
        TokenList_append(list, Token_new(RIGHT_BRACE, NULL));
        break;
      case '!': {
        if (input[i + 1] == '=') {
          TokenList_append(list, Token_new(NOT_EQUAL, NULL));
          i++;
        } else {
          TokenList_append(list, Token_new(NOT, NULL));
        }
        break;
      }
      case '"': {// string literals
        int j = i + 1;
        while (input[j] != '"' && (size_t) j < strlen(input)) {
          j++;
        }
        char* LiteralValue = (char*) calloc(j - i + 1, sizeof(char));
        LiteralValue = (char*) memcpy(LiteralValue, input + i + 1, j - i - 1);
        LiteralValue[j - i] = '\0';
        TokenList_append(list, Token_new(STRING, LiteralValue));
        i = j;
        break;
      }
      case '\'': {// character literals
        char* LiteralValue = (char*) malloc(2);
        LiteralValue[0] = input[i + 1];
        LiteralValue[1] = 0;
        TokenList_append(list, Token_new(CHARACTER, LiteralValue));
        i += 2;
        break;
      }
      case '/': {
        TokenList_append(list, Token_new(FORWARD_SLASH, NULL));
        break;
      }
      case '>': {
        if (list->tail->prev && list->tail->prev->prev && list->tail->prev->prev->prev &&
            list->tail->prev->prev->prev->token->type == INCLUDE) {
          // if part of an include then ignore this
          break;
        } else {
          if (input[i + 1] == '=') {
            TokenList_append(list, Token_new(GREATER_EQUAL, NULL));
            i++;
          } else {
            TokenList_append(list, Token_new(GREATER, NULL));
          }
          break;
        }
      }
      case '<': {
        if (list->tail && list->tail->token &&
            list->tail->token->type == INCLUDE) {
          // if previous token is an include then ignore this
          break;
        } else {
          if (input[i + 1] == '=') {
            TokenList_append(list, Token_new(LESS_EQUAL, NULL));
            i++;
          } else {
            TokenList_append(list, Token_new(LESS, NULL));
          }
        }
        break;
      }
      case '=': {
        if (input[i + 1] == '=') {
          TokenList_append(list, Token_new(EQUAL_EQUAL, NULL));
        } else {
          TokenList_append(list, Token_new(EQUAL, NULL));
        }
        break;
      }
      case '\t':
      case '\r':
      case ' ':
      case '\n':
        break;
      default: {
        if (isalnum(input[i])) {
          // found an identifier or keyword
          // extract and compare to keywords
          int j = i + 1;
          while ((isalnum(input[j]) || input[j] == '_') &&
                 (size_t) j < strlen(input)) {
            j++;
          }
          char* LiteralValue = (char*) malloc(j - i + 1);
          LiteralValue = (char*) memcpy(LiteralValue, input + i, j - i);
          LiteralValue[j - i] = '\0';
          i = j - 1;

          if (strcmp(LiteralValue, "int") == 0) {
            TokenList_append(list, Token_new(INT, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "void") == 0) {
            TokenList_append(list, Token_new(VOID, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "if") == 0) {
            TokenList_append(list, Token_new(IF, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "else") == 0) {
            TokenList_append(list, Token_new(ELSE, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "while") == 0) {
            TokenList_append(list, Token_new(WHILE, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "for") == 0) {
            TokenList_append(list, Token_new(FOR, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "return") == 0) {
            TokenList_append(list, Token_new(RETURN, NULL));
            free(LiteralValue);
          } else if (strcmp(LiteralValue, "include") == 0 &&
                     list->tail->token->type == HASH) {
            if (list->tail->token->literal) {
              free(list->tail->token->literal);
            }
            TokenList_remove_tail(list);
            TokenList_append(list, Token_new(INCLUDE, NULL));
            free(LiteralValue);
          } else {
            TokenList_append(list, Token_new(IDENTIFIER, LiteralValue));
          }

        } else {
          printf("Unknown token: %c\n", input[i]);
        }
      }
    }
    i++;
  }

  free(input);

  // when parsing a #include <library.h> it is split into the tokens: INCLUDE library DOT h next -> INCLUDE library.h next
  // combine them into a single token for the library name               ppp   pp     p  c  n
  TokenListNode* temp = list->head;
  while (temp != NULL) {
    if (temp->prev && temp->prev->prev && temp->prev->prev->prev && temp->prev->prev->prev->token->type == INCLUDE && temp->token->type == IDENTIFIER && temp->prev->token->type == DOT) {
      // create the new token
      char* newLiteral;
      asprintf(&newLiteral, "%s.h", (char*) temp->prev->prev->token->literal);
      Token* t = Token_new(IDENTIFIER, newLiteral);
      Token_free(temp->prev->prev->token);
      temp->prev->prev->token = t;
      temp->prev->prev->next = temp->next;
      temp = temp->next;
    } else {
      temp = temp->next;
    }
  }

  return list;
}
