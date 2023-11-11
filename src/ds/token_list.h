#include "tokens.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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

void tokenlist_Print(list_t *list) {
  struct listNode *node = list->head;
  printf("[ ");
  while (node != NULL) {
    if (node->token->type == STRING || node->token->type == CHARACTER) {
      printf("%s(\"%s\") ", tokenTypeAsString(node->token->type),
             (char *)node->token->literal);
    } else if (node->token->type == IDENTIFIER) {
      printf("%s ", (char *)node->token->literal);
    } else {
      printf("%s ", tokenTypeAsString(node->token->type));
    }
    node = node->next;
  }
  printf("]\n");
}

list_t *tokenlist_Initialise() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void tokenlist_Append(list_t *list, token_t *t) {
  listNode_t *newNode = (listNode_t *)malloc(sizeof(listNode_t));
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

void tokenlist_RemoveTail(list_t *list) {
  if (list->size == 0) {
    return;
  } else if (list->size == 1) {
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return;
  }
  listNode_t *temp = list->tail;
  list->tail = list->tail->prev;
  list->tail->next = NULL;
  free(temp);
  list->size--;
}

void tokenlist_Free(list_t *list) {
  listNode_t *temp = list->head;
  while (temp != NULL) {
    token_t *t = temp->token;
    if (t->literal) {
      free(t->literal);
    }
    free(t);
    temp = temp->next;
  }
  while (list->size > 0) {
    tokenlist_RemoveTail(list);
  }
  free(list);
}

void scanToken(char *input, list_t *list) {
  uint i = 0;
  while (i < strlen(input)) {
    switch (input[i]) {
    case '#':
      tokenlist_Append(list, token_new(HASH, NULL));
      break;
    case '(':
      tokenlist_Append(list, token_new(LEFT_PAREN, NULL));
      break;
    case ')':
      tokenlist_Append(list, token_new(RIGHT_PAREN, NULL));
      break;
    case '[':
      tokenlist_Append(list, token_new(LEFT_BRACKET, NULL));
      break;
    case ']':
      tokenlist_Append(list, token_new(RIGHT_BRACKET, NULL));
      break;
    case ';':
      tokenlist_Append(list, token_new(SEMICOLON, NULL));
      break;
    case ',':
      tokenlist_Append(list, token_new(COMMA, NULL));
      break;
    case '.':
      tokenlist_Append(list, token_new(DOT, NULL));
      break;
    case '+':
      tokenlist_Append(list, token_new(PLUS, NULL));
      break;
    case '-':
      tokenlist_Append(list, token_new(MINUS, NULL));
      break;
    case '*':
      tokenlist_Append(list, token_new(ASTERISK, NULL));
      break;
    case '{':
      tokenlist_Append(list, token_new(LEFT_BRACE, NULL));
      break;
    case '}':
      tokenlist_Append(list, token_new(RIGHT_BRACE, NULL));
      break;
    case '!': {
      if (input[i + 1] == '=') {
        tokenlist_Append(list, token_new(NOT_EQUAL, NULL));
        i++;
      } else {
        tokenlist_Append(list, token_new(NOT, NULL));
      }
      break;
    }
    case '"': { // string literals
      int j = i + 1;
      while (input[j] != '"' && (size_t)j < strlen(input)) {
        j++;
      }
      char *LiteralValue = (char *)malloc(j - i);
      LiteralValue = (char *)memcpy(LiteralValue, input + i + 1, j - i - 1);
      LiteralValue[j - i] = '\0';
      tokenlist_Append(list, token_new(STRING, LiteralValue));
      i = j;
      break;
    }
    case '\'': { // character literals
      char *LiteralValue = (char *)malloc(2);
      LiteralValue[0] = input[i + 1];
      LiteralValue[1] = 0;
      tokenlist_Append(list, token_new(CHARACTER, LiteralValue));
      i += 2;
      break;
    }
    case '/': {
      tokenlist_Append(list, token_new(FORWARD_SLASH, NULL));
      break;
    }
    case '>': {
      if (list->tail->prev && list->tail->prev && list->tail->prev->prev &&
          list->tail->prev->prev->token->type == INCLUDE) {
        break;
      } else {
        if (input[i + 1] == '=') {
          tokenlist_Append(list, token_new(GREATER_EQUAL, NULL));
          i++;
        } else {
          tokenlist_Append(list, token_new(GREATER, NULL));
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
          tokenlist_Append(list, token_new(LESS_EQUAL, NULL));
          i++;
        } else {
          tokenlist_Append(list, token_new(LESS, NULL));
        }
      }
      break;
    }
    case '=': {
      if (input[i + 1] == '=') {
        tokenlist_Append(list, token_new(EQUAL_EQUAL, NULL));
      } else {
        tokenlist_Append(list, token_new(EQUAL, NULL));
      }
      break;
    }
    case '\t':
      break;
    case '\r':
      break;
    case ' ':
      break;
    case '\n':
      break;
    default: {
      if (isalnum(input[i])) {
        // found an identifier or keyword
        // extract and compare to keywords
        int j = i + 1;
        while ((isalnum(input[j]) || input[j] == '_') &&
               (size_t)j < strlen(input)) {
          j++;
        }
        char *LiteralValue = (char *)malloc(j - i);
        LiteralValue = (char *)memcpy(LiteralValue, input + i, j - i);
        LiteralValue[j - i] = '\0';
        i = j - 1;

        if (strcmp(LiteralValue, "int") == 0) {
          tokenlist_Append(list, token_new(INT, NULL));
        } else if (strcmp(LiteralValue, "void") == 0) {
          tokenlist_Append(list, token_new(VOID, NULL));
        } else if (strcmp(LiteralValue, "if") == 0) {
          tokenlist_Append(list, token_new(IF, NULL));
        } else if (strcmp(LiteralValue, "else") == 0) {
          tokenlist_Append(list, token_new(ELSE, NULL));
        } else if (strcmp(LiteralValue, "while") == 0) {
          tokenlist_Append(list, token_new(WHILE, NULL));
        } else if (strcmp(LiteralValue, "for") == 0) {
          tokenlist_Append(list, token_new(FOR, NULL));
        } else if (strcmp(LiteralValue, "return") == 0) {
          tokenlist_Append(list, token_new(RETURN, NULL));
        } else if (strcmp(LiteralValue, "include") == 0 &&
                   list->tail->token->type == HASH) {
          free(list->tail->token);
          tokenlist_RemoveTail(list);
          tokenlist_Append(list, token_new(INCLUDE, NULL));
        } else {
          tokenlist_Append(list, token_new(IDENTIFIER, LiteralValue));
        }

      } else {
        printf("Unknown token: %c\n", input[i]);
      }
    }
    }
    i++;
  }
}
