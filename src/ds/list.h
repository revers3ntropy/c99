#ifndef linkedList_H
#define linkedList_H

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
  void *data;
  struct listNode *next;
  struct listNode *prev;
} listNode_t;

typedef struct listContainer {
  int size;
  struct listNode *head;
  struct listNode *tail;
} list_t;

void list_Print(list_t *list);

list_t *list_Initialise();

void list_Prepend(list_t *list, void *data);

void list_Append(list_t *list, void *data);

void list_RemoveTail(list_t *list);

void list_RemoveHead(list_t *list);

void list_Free(list_t *list);

#endif
