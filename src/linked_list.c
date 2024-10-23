#include "linked_list.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
  struct LinkedListNode *head;
  size_t length;
};

struct LinkedListNode {
  struct LinkedListNode *next;
  int32_t value;
};

LinkedList *linked_list_init(void) {
  LinkedList *list = calloc(1, sizeof(LinkedList));
  if (list == NULL)
    return NULL;

  list->head = NULL;
  list->length = 0;

  return list;
}

struct LinkedList *linked_list_of(size_t length, ...) {
  va_list arguments;
  va_start(arguments, length);

  LinkedList *list = linked_list_init();
  struct LinkedListNode *current = list->head;
  for (size_t index = 0; index < length; index++) {
    struct LinkedListNode *node = calloc(1, sizeof(struct LinkedListNode));
    if (node == NULL)
      continue;

    node->next = NULL;
    node->value = va_arg(arguments, int);

    list->length++;

    if (current == NULL) {
      list->head = current = node;
      continue;
    }

    current->next = node;
    current = node;
  }
  va_end(arguments);

  return list;
}

void linked_list_free(LinkedList **mutList) {
  if (mutList == NULL)
    return;

  LinkedList *list = *mutList;
  if (list == NULL)
    return;

  int32_t value = 0;
  while (list->head != NULL) {
    linked_list_shift(list, &value);
  }

  free(list);
  *mutList = NULL;
}

size_t linked_list_length(LinkedList *list) {
  if (list == NULL)
    return 0;

  return list->length;
}

bool linked_list_push(LinkedList *list, int32_t value) {
  if (list == NULL)
    return false;

  struct LinkedListNode *node = calloc(1, sizeof(struct LinkedListNode));
  if (node == NULL)
    return false;

  node->value = value;
  node->next = NULL;

  list->length++;

  if (list->head == NULL) {
    list->head = node;
    return true;
  }

  struct LinkedListNode *current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = node;
  return true;
}

bool linked_list_unshift(LinkedList *list, int32_t value) {
  if (list == NULL)
    return false;

  struct LinkedListNode *node = calloc(1, sizeof(struct LinkedListNode));
  if (node == NULL)
    return false;

  node->value = value;
  node->next = list->head;

  list->head = node;
  list->length++;

  return true;
}

bool linked_list_pop(LinkedList *list, int32_t *result) {
  if (list == NULL || list->head == NULL) {
    return false;
  }

  list->length--;

  struct LinkedListNode *node = list->head;
  struct LinkedListNode *previousNode = NULL;
  while (node->next != NULL) {
    previousNode = node;
    node = node->next;
  }

  *result = node->value;

  if (previousNode == NULL) {
    list->head = NULL;
  } else {
    previousNode->next = NULL;
  }

  free(node);
  return true;
}

bool linked_list_shift(LinkedList *list, int32_t *value) {
  if (list == NULL || list->head == NULL) {
    value = NULL;
    return false;
  }

  list->length--;

  struct LinkedListNode *node = list->head;
  *value = node->value;
  list->head = node->next;

  free(node);
  return true;
}

void *linked_list_it_begin(LinkedList *list) {
  if (list == NULL)
    return NULL;

  return list->head;
}

void *linked_list_it_next(void *cursor) {
  if (cursor == NULL)
    return NULL;

  struct LinkedListNode *node = cursor;
  cursor = node->next;

  return cursor;
}

int32_t linked_list_it_value(void *cursor) {
  if (cursor == NULL)
    return 0;

  struct LinkedListNode *node = cursor;

  return node->value;
}

bool linked_list_get(LinkedList *list, size_t index, int32_t *value) {
  if (list == NULL)
    return false;

  struct LinkedListNode *node = list->head;
  for (size_t i = 0; i < index; i++) {
    if (node == NULL)
      break;
    node = node->next;
  }

  if (node == NULL)
    return false;

  *value = node->value;
  return true;
}

LinkedList *linked_list_from(LinkedList *source) {
  LinkedList *list = linked_list_init();
  if (source == NULL)
    return list;

  struct LinkedListNode *current = list->head;
  for (void *cursor = linked_list_it_begin(source); cursor != NULL;
       cursor = linked_list_it_next(cursor)) {
    struct LinkedListNode *node = calloc(1, sizeof(struct LinkedListNode));
    if (node == NULL)
      continue;

    node->next = NULL;
    node->value = linked_list_it_value(cursor);

    list->length++;

    if (current == NULL) {
      list->head = current = node;
      continue;
    }

    current->next = node;
    current = node;
  }

  return list;
}
