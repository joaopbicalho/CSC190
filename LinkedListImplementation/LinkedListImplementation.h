/* FILE linked_list.h
 *    Interface for functions to manipulate multiple linked lists of ints.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* TYPE list_t
 *    The type for a linked list of ints.
 */
typedef struct list list_t;

/* FUNCTION list_create
 *    Allocate memory for a new linked list.
 * Parameters and preconditions:  none
 * Return value:
 *    a pointer to a new empty linked list of ints -- NULL in case of error
 * Side-effects:
 *    memory has been allocated for the new list
 */
list_t *list_create(void);

/* FUNCTION list_destroy
 *    Release all of the memory allocated for a linked list.
 * Parameters and preconditions:
 *    list != NULL: a linked list of ints
 * No return value.
 * Side-effects:
 *    all the memory allocated for the list has been freed
 */
void list_destroy(list_t *list);

/* FUNCTION size
 * Return the number of items in a linked list.
 * Parameter and preconditions:
 *    list != NULL: a linked list of ints
 * Return value:
 *    the number of items currently in the list
 * Side-effects:  none
 */
size_t list_size(const list_t *list);

/* FUNCTION list_get
 * Return the item at index i in a linked list.
 * Parameters and preconditions:
 *    list != NULL: a linked list of ints
 *    i: index of retrieval, 0 <= i < list_size(list)
 * Return value:
 *   the item at index i in the list
 * Side-effects:  none
 */
int list_get(const list_t *list, size_t i);

/* FUNCTION list_insert
 * Insert x at index i in a linked list.
 * Parameters and preconditions:
 *    list != NULL: a linked list of ints
 *    i: index of insertion, 0 <= i <= list_size(list)
 *    x: value to insert
 * Return value:  none
 * Side-effects:
 *    value x has been inserted at index i in the list
 */
void list_insert(list_t *list, size_t i, int x);

/* FUNCTION list_remove
 * Remove the item at index i from a linked list.
 * Parameters and preconditions:
 *    list != NULL: a linked list of ints
 *    i: index of deletion, 0 <= i < list_size(list)
 * Return value:  none
 * Side-effects:
 *    value x has been removed from index i in the list
 */
void list_remove(list_t *list, size_t i);

#endif/*LINKED_LIST_H*/
