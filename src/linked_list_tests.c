#include "linked_list_tests.h"
#include "linked_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int linked_list_tests(void) {
  LinkedList *list = linked_list_of(3, -1, 0, 1);
  printf("length: %lu\n", linked_list_length(list));
  for (void *cursor = linked_list_it_begin(list); cursor != NULL;
       cursor = linked_list_it_next(cursor)) {
    printf("%d->", linked_list_it_value(cursor));
  }
  printf("\n");

  linked_list_push(list, 42);
  printf("length: %lu\n", linked_list_length(list));
  linked_list_unshift(list, -42);
  printf("length: %lu\n", linked_list_length(list));

  for (void *cursor = linked_list_it_begin(list); cursor != NULL;
       cursor = linked_list_it_next(cursor)) {
    printf("%d->", linked_list_it_value(cursor));
  }
  printf("\n");

  int32_t value = 0;
  linked_list_pop(list, &value);
  printf("poped value %d\n", value);
  printf("length: %lu\n", linked_list_length(list));

  linked_list_shift(list, &value);
  printf("shifted value %d\n", value);
  printf("length: %lu\n", linked_list_length(list));

  for (void *cursor = linked_list_it_begin(list); cursor != NULL;
       cursor = linked_list_it_next(cursor)) {
    printf("%d->", linked_list_it_value(cursor));
  }
  printf("\n");

  linked_list_get(list, 2, &value);
  printf("value at index 2: %d\n", value);

  linked_list_free(&list);
  printf("list is NULL: %s", list == NULL ? "true" : "false");

  return 0;
}

void menu_print(void);
int menu_choose_option(void);
int menu_read_int(void);
void menu_print_list(LinkedList *list);
void menu_push_list(LinkedList *list);
void menu_unshift_list(LinkedList *list);
void menu_pop_list(LinkedList *list);
void menu_shift_list(LinkedList *list);
void menu_get_list(LinkedList *list);

int linked_list_cli(void) {
  LinkedList *list = linked_list_init();

  printf("Welcome to your LinkedList CLI\n");
  while (true) {
    menu_print();
    int option = menu_choose_option();
    if (option == 0)
      break;

    switch (option) {
    case 1:
      menu_print_list(list);
      break;
    case 2:
      menu_push_list(list);
      break;
    case 3:
      menu_unshift_list(list);
      break;
    case 4:
      menu_pop_list(list);
      break;
    case 5:
      menu_shift_list(list);
      break;
    case 6:
      menu_get_list(list);
      break;
    }
  }

  return 0;
}

void menu_print(void) {
  printf("Choose your options to manipulate the list\n");
  printf("1. print the list\n");
  printf("2. push (at the end)\n");
  printf("3. unshift (at the beggining)\n");
  printf("4. pop (at the end)\n");
  printf("5. shift (at the beggining)\n");
  printf("6. get value at index\n");
  printf("0. exit\n");
}

int menu_choose_option(void) {
  int result = 0;

  while (true) {
    result = menu_read_int();
    if (result >= 0 && result <= 6)
      break;
    printf("Sorry, this option is invalid\n");
  }

  return result;
}

int menu_read_int(void) {
  int result = 0;
  while (!scanf("%d", &result)) {
  }
  return result;
}

void menu_print_list(LinkedList *list) {
  printf("list length: %lu\n", linked_list_length(list));
  for (void *cursor = linked_list_it_begin(list); cursor != NULL;
       cursor = linked_list_it_next(cursor)) {
    printf("%d->", linked_list_it_value(cursor));
  }
  printf("\n");
}

void menu_push_list(LinkedList *list) {
  printf("What number do you want to add?: ");
  int value = menu_read_int();

  linked_list_push(list, value);
}

void menu_unshift_list(LinkedList *list) {
  printf("What number do you want to add?: ");
  int value = menu_read_int();

  linked_list_unshift(list, value);
}

void menu_pop_list(LinkedList *list) {
  int32_t pop = 0;
  if (!linked_list_pop(list, &pop)) {
    printf("List is empty, nothing to pop.\n");
    return;
  }

  printf("value pop: %d\n", pop);
}

void menu_shift_list(LinkedList *list) {
  int32_t shift = 0;
  if (!linked_list_shift(list, &shift)) {
    printf("List is empty, nothing to shift.\n");
    return;
  }

  printf("value shift: %d\n", shift);
}

void menu_get_list(LinkedList *list) {
  printf("At what index do you want obtain the value? ");
  int index = menu_read_int();

  int32_t value = 0;
  if (!linked_list_get(list, index, &value)) {
    printf("List overflow, nothing at this index.\n");
    return;
  }

  printf("value at list[%d]: %d\n", index, value);
}
