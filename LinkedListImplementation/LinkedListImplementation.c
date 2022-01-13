/* FILE linked_list.c
 *    Implementation of the functions in linked_list.h.
 */

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


/* TYPE node_t
 *    The type for a node storing an int.
 */
typedef struct node {
    int data;
    struct node *next;
} node_t;

/* Definition of the list structure. */
struct list {
    size_t size;   /* number of elements in the list, after header */
    node_t header; /* header node at the front of the list         */
};


/* FUNCTION get_node
 *    Return a pointer to the node at index i-1 in the list.
 * Parameters and preconditions:
 *    i: index of retrieval, 0 <= i <= size() + 1
 * Return value:
 *    a pointer to the node at index i-1 -- the header has index -1, NULL is at
 *    index size()
 * Side-effects:  none
 */
node_t *get_node(list_t *list, size_t i)
{
    node_t *current = &(list->header);
    while (i-- > 0)  current = current->next;
    return current;
}


/* FUNCTION list_create -- see header file for full description
 */
list_t *list_create(void)
{
    list_t *list = malloc(sizeof(struct list));
    if (list) {
        list->size = 0;
        list->header.data = 0; // not necessary
        list->header.next = NULL;
    }
    return list;
}


/* FUNCTION list_destroy -- see header file for full description
 */
void list_destroy(list_t *list)
{
    node_t *current = list->header.next;
    while (current) {
        list->header.next = current->next;
        free(current);
        current = list->header.next;
    }
    free(list);
}


/* FUNCTION list_size -- see header file for full description
 */
size_t list_size(const list_t *list)
{
    return list->size;
}


/* FUNCTION get -- see header file for full description
 */
int list_get(const list_t *list, size_t i)
{
    return get_node((list_t *) list, i+1)->data;
}


/* FUNCTION insert -- see header file for full description
 */
void list_insert(list_t *list, size_t i, int x)
{
    node_t *previous = get_node(list, i);
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fputs("ERROR: Unable to allocate memory!\n", stderr);
        exit(EXIT_FAILURE);
    }
    new_node->data = x;
    new_node->next = previous->next;
    previous->next = new_node;
    list->size++;
}


/* FUNCTION delete -- see header file for full description
 */
void list_remove(list_t *list, size_t i)
{
    node_t *previous = get_node(list, i);
    node_t *old_node = previous->next;
    previous->next = old_node->next;
    free(old_node);
    list->size--;
}
