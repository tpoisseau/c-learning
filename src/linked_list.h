#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Contains int32_t
 * */
typedef struct LinkedList LinkedList;

/**
 * Init empty list
 *
 * @example
 *
 * ```c
 * LinkedList *list = linked_list_init();
 * ```
 * */
LinkedList *linked_list_init(void);

/**
 * Init list with variadic arguments as items.
 * Variadic arguments must be a list of int32_t
 *
 * @example
 *
 * ```c
 * LinkedList *list = linked_list_of(3, 0, 1, 2)
 * // 0->1->2
 * ```
 * */
LinkedList *linked_list_of(size_t length, ...);

void linked_list_free(LinkedList **list);

/**
 * Get length of the list
 * */
size_t linked_list_length(LinkedList *list);

/**
 * Push value at the end of the list
 * */
bool linked_list_push(LinkedList *list, int32_t value);

/**
 * Add an element at the beginning of the list
 * */
bool linked_list_unshift(LinkedList *list, int32_t value);

/**
 * remove the last element of the list and set the corresponding value into the
 * value pointer.
 *
 * @return true if pop with success, false otherwise
 *
 * @example
 *
 * ```c
 * LinkedList* list;
 *
 * int32_t result = 0;
 * if(!linked_list_pop(list, &result)) {
 *	// nothing to pop
 * }
 * else {
 * 	// do something with result
 * }
 *
 * linked_list_push(list, 42);
 * linked_list_pop(list, result);
 *
 * // result == 42
 * ```
 * */
bool linked_list_pop(LinkedList *list, int32_t *value);

/**
 * Same than `linked_list_pop` but remove the first element of the list
 * */
bool linked_list_shift(LinkedList *list, int32_t *value);

/**
 * @return true if get with success, false otherwise
 * assign result at index to value
 * */
bool linked_list_get(LinkedList *list, size_t index, int32_t *value);

/**
 * return a cursor of for the
 *
 * @example
 * ```c
 * #include "linked_list.h";
 *
 * LinkedList* list = linked_list_of(3, 0, 1, 2);
 * for (void* cursor = linked_list_begin(list); cursor != NULL; cursor =
 *linked_list_next(cursor)) { printf("%d->", linked_list_it_value(cursor));
 * }
 * printf("\n");
 * linked_list_free(&list);
 * ```
 */
void *linked_list_it_begin(LinkedList *list);

/**
 * return cursor next to the given cursor
 *
 * @example
 * ```c
 * cursor = linked_list_it_next(cursor);
 *
 * */
void *linked_list_it_next(void *cursor);

/**
 * return value from cursor (default to 0 if cursor is NULL)
 * */
int32_t linked_list_it_value(void *cursor);

/**
 * return a copy of the list
 * */
LinkedList *linked_list_from(LinkedList *source);
