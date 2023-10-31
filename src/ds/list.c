#include "list.h"

void list_Print(list_t *list) {
  listNode_t *temp = list->head;
  printf("[ ");
  while (temp != NULL) {
    printf("%d ", *(int *)temp->data);
    temp = temp->next;
  }
  printf("]\n");
}

list_t *list_Initialise() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void list_Prepend(list_t *list, void *data) {
  listNode_t *newNode = (listNode_t *)malloc(sizeof(listNode_t));
  newNode->data = data;
  if (list->size == 0) {
    newNode->next = NULL;
    newNode->prev = NULL;
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->next = list->head;
    newNode->prev = NULL;
    list->head->prev = newNode;
    list->head = newNode;
  }
  list->size++;
}

void list_Append(list_t *list, void *data) {
  listNode_t *newNode = (listNode_t *)malloc(sizeof(listNode_t));
  newNode->data = data;
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

void list_RemoveTail(list_t *list) {
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

void list_RemoveHead(list_t *list) {
  if (list->size == 0) {
    return;
  } else if (list->size == 1) {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return;
  }
  listNode_t *temp = list->head;
  list->head = list->head->next;
  list->size--;
  free(temp);
}

void list_Free(list_t *list) {
  while (list->size > 0) {
    list_RemoveTail(list);
  }
  free(list);
}

