#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFileToString(char *filename) {
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

char *removeSingleLineComments(char *str) {
  // remove all single comments from the string
  char *newStr = (char *)malloc(strlen(str) + 1);
  newStr[strlen(str)] = '\0';
  memset(newStr, ' ', strlen(str));
  int length = strlen(str);
  int newStringptr = 0;
  for (int i = 1; i < length; i++) {
    if (str[i - 1] == '/' && str[i] == '/') {
      for (int j = i + 1; j < length; j++) {
        if (str[j] == '\n' || str[j] == EOF) {
          i = j + 2;
        }
      }
    }
    newStr[newStringptr] = str[i - 1];
    newStringptr++;
  }
  free(str);
  return newStr;
}

char *removeMultilineComments(char *str) {
  // remove all multiline comments from the string
  char *newStr = (char *)malloc(strlen(str) + 1);
  newStr[strlen(str)] = '\0';
  memset(newStr, ' ', strlen(str));
  int length = strlen(str);
  int newStringptr = 0;
  for (int i = 1; i < length; i++) {
    if (str[i - 1] == '/' && str[i] == '*') {
      for (int j = i + 1; j < length; j++) {
        if (str[j - 1] == '*' && str[j] == '/') {
          i = j + 2;
        }
      }
    }
    newStr[newStringptr] = str[i - 1];
    newStringptr++;
  }
  free(str);
  return newStr;
}

char *trimAllChars(char *str) {
  char *newStr = (char *)malloc(strlen(str));
  newStr[strlen(str)] = '\0';
  memset(newStr, ' ', strlen(str));
  int newStringptr = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
      newStr[newStringptr] = str[i];
      newStringptr++;
    }
  }
  free(str);
  str = (char *)malloc(newStringptr + 1);
  str[newStringptr] = '\0';
  memcpy(str, newStr, newStringptr);
  return str;
}

char *processFile(char *file) {
  char *fileBuf = readFileToString(file);
  fileBuf = removeSingleLineComments(fileBuf);
  fileBuf = removeMultilineComments(fileBuf);
  fileBuf = trimAllChars(fileBuf);
  printf("%s\n", fileBuf);
  return fileBuf;
}
