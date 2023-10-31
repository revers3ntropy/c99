#ifndef LEXER_H
#define LEXER_H

#include "ds/list.h"

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
  LEFT_BRACE = '{',
  RIGHT_BRACE = '}',
  LEFT_PAREN = '(',
  RIGHT_PAREN = ')',
  SEMICOLON = ';',
  HASH = '#',
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
  void *value;
  tokenType type;
} token_t;

void printTokenList(list_t *list) {
  if (list == NULL || list->size == 0) {
    printf("[]\n");
    return;
  }
  listNode_t *temp = list->head;
  printf("[ ");
  while (temp != NULL) {
    token_t *token = ((token_t *)temp->data);
    if (token->type == STRING_LITERAL) {
      printf("\"%s\" ", (char *)(token->value));
    } else if (token->type == CHAR_LITERAL) {
      printf("\'%c\' ", (char)(token->type));
    } else if (token->type == INTEGER_LITERAL) {
      printf("%d ", *((int *)(token->value)));
    } else if (token->type == IDENTIFIER) {
      printf("%s ", (char *)(token->value));
    } else {
      printf("%c ", (char)(token->type));
    }
    temp = temp->next;
  }
  printf("]\n");
}

token_t *newToken(void *value, tokenType type) {
  token_t *token = (token_t *)malloc(sizeof(token_t));
  if (token == NULL) {
    printf("Error allocating memory for a new token struct\n");
    return NULL;
  }
  token->value = value;
  token->type = type;
  return token;
}

char *readFileToString(char *filename) {
  if (filename == NULL) {
    return NULL;
  }
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("File cannot be opened or does not exist\n");
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *string = (char *)malloc(fsize + 1);
  if (string == NULL) {
    printf("Error allocating memory\n");
    return NULL;
  }

  if (fread(string, fsize, 1, fp) == 0) {
    printf("Error reading file\n");
    return NULL;
  }

  fclose(fp);
  string[fsize] = 0;
  return string;
}

char *removeAllComments(char *str) {
  if (str == NULL) {
    return NULL;
  }
  int length = strlen(str);
  for (int i = 1; i < length; i++) {
    if (str[i - 1] == '/' && str[i] == '*') {
      int j = i;
      while (j != length && !(str[j - 1] == '*' && str[j] == '/')) {
        j++;
      }
      memset(str + i - 1, '`', j - i + 2);
      i = j;
    } else if (str[i - 1] == '/' && str[i] == '/') {
      int j = i;
      while (j != length && !(str[j] == '\n' || str[j] == '\0')) {
        j++;
      }
      memset(str + i - 1, '`', j - i + 1);
      i = j;
    }
  }
  int contigousIndex = 0;
  for (int i = 0; i < length; i++) {
    if (str[i] != '`') {
      str[contigousIndex] = str[i];
      contigousIndex++;
    }
  }
  str[contigousIndex] = '\0';
  str = (char *)realloc(str, contigousIndex + 1);
  return str;
}

list_t *tokenise(char *str) {
  list_t *tokens = list_Initialise();
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == HASH) {
      list_Append(tokens, (void *)newToken((void *)HASH, HASH));
    } else if (str[i] == LEFT_BRACE) {
      list_Append(tokens, (void *)newToken((void *)LEFT_BRACE, LEFT_BRACE));
    } else if (str[i] == RIGHT_BRACE) {
      list_Append(tokens, (void *)newToken((void *)RIGHT_BRACE, RIGHT_BRACE));
    } else if (str[i] == LEFT_PAREN) {
      list_Append(tokens, (void *)newToken((void *)LEFT_PAREN, LEFT_PAREN));
    } else if (str[i] == RIGHT_PAREN) {
      list_Append(tokens, (void *)newToken((void *)RIGHT_PAREN, RIGHT_PAREN));
    } else if (str[i] == SEMICOLON) {
      list_Append(tokens, (void *)newToken((void *)SEMICOLON, SEMICOLON));
    } else if (str[i] == ADDITION) {
      list_Append(tokens, (void *)newToken((void *)ADDITION, ADDITION));
    } else if (str[i] == SUBTRACTION) {
      list_Append(tokens, (void *)newToken((void *)SUBTRACTION, SUBTRACTION));
    } else if (str[i] == ASTERISK) {
      list_Append(tokens, (void *)newToken((void *)ASTERISK, ASTERISK));
    } else if (str[i] == DIVISION) {
      list_Append(tokens, (void *)newToken((void *)DIVISION, DIVISION));
    } else if (str[i] == LEFT_CROCODILE) {
      list_Append(tokens,
                  (void *)newToken((void *)LEFT_CROCODILE, LEFT_CROCODILE));
    } else if (str[i] == RIGHT_CROCODILE) {
      list_Append(tokens,
                  (void *)newToken((void *)RIGHT_CROCODILE, RIGHT_CROCODILE));
    } else if (str[i] == LEFT_SQUARE_BRACKET) {
      list_Append(tokens, (void *)newToken((void *)LEFT_SQUARE_BRACKET,
                                           LEFT_SQUARE_BRACKET));
    } else if (str[i] == RIGHT_SQUARE_BRACKET) {
      list_Append(tokens, (void *)newToken((void *)RIGHT_SQUARE_BRACKET,
                                           RIGHT_SQUARE_BRACKET));
    } else if (str[i] == '\'') {
      if (str[i + 2] != '\'') {
        printf("Invalid literal, character literal must be one character and "
               "properly terminated\n");
        exit(1);
      } else {
        char *literalValue = (char *)malloc(sizeof(char) * 2);
        literalValue[0] = str[i + 1];
        literalValue[1] = '\0';
        i += 2;
        list_Append(tokens,
                    (void *)newToken((void *)literalValue, CHAR_LITERAL));
      }
    } else if (str[i] == 34) {
      int j = i + 1;
      while (str[j] != 34) {
        j++;
      }
      // access str[i+1] to str[j-1] for the value of literal
      char *LiteralValue = (char *)malloc(j - i);
      LiteralValue = (char *)memcpy(LiteralValue, str + i + 1, j-i-1);
      LiteralValue[j-i] = '\0';
      list_Append(tokens,
                  (void *)newToken((void *)LiteralValue, STRING_LITERAL));
      i = j + 1;
    } else if (isdigit(str[i])) {
      int j = 0;
      while (isdigit(str[i + j])) {
        j++;
      }
      // access str[i] and str[i+j] for the value of the literal
      char *LiteralString = (char *)malloc(j + 1);
      LiteralString[strlen(LiteralString)] = '\0';
      LiteralString = (char *)memcpy((char *)LiteralString, str + i, j);
      int *value = (int *)malloc(sizeof(int));
      // set what is pointed to by value to the integer value of LiteralString
      *value = atoi(LiteralString);
      list_Append(tokens, (void *)newToken((void *)value, INTEGER_LITERAL));
      i = i + j - 1;
    } else if (isalpha(str[i])) {
        // attempt to parse an identifier 
        int j = 0;
        while (isalpha(str[i + j])) {
          j++;
        }
        char *identifier = (char *)malloc(j + 1);
        identifier[j] = '\0';
        identifier = (char *)memcpy((char *)identifier, str + i, j);
        list_Append(tokens, (void *)newToken((void *)identifier, IDENTIFIER));
        i = i + j - 1;
    }
  }
  return tokens;
}

char *processFile(char *file) {
  char *fileBuf = readFileToString(file);
  fileBuf = removeAllComments(fileBuf);
  return fileBuf;
}

#endif
