#include "lab.h"
#include <stdlib.h>


// The AI came up with the plans I implemented my own code.

// Assisted By AI
typedef struct ListNode {
	void *data;
	struct ListNode* next; // Pointer to the next node
} ListNode;

// Assisted By AI
struct List {
	ListNode *head; // Pointer to the sentinel node
	size_t size;
	// Add other fields as needed
};

// Assisted By AI
List *list_create(ListType type) {
  	/*
	 * PLAN for list_Create:
	 * 1. Allocate memory for the List structure
	 *    - If allocation fails, return false.
	 * 2. Allocate memory for the sentinel node (ListNode)
	 * 3. Set the sentinel node’s data to NULL
	 * 4. Set the sentinel node’s next pointer to NULL (list is empty)
	 * 5. Set the list’s head (or sentinel) pointer to the sentinel node
	 * 6. Set the list’s size to 0
	 * 7. Return the pointer to the new list
	 */

    List *list = malloc(sizeof(List));
    if (!list) return NULL;

    ListNode *sentinel = malloc(sizeof(ListNode));
    if (!sentinel) { free(list); return NULL; }

    sentinel->data = NULL;

    sentinel->next = NULL;

    list->head = sentinel;

    list->size = 0;

    return list;
}

// Assisted By AI
void list_destroy(List *list, FreeFunc free_func) {
	/*
	 * PLAN for list_destroy:
	 * 1. Start from the first real node (list->head->next).
	 * 2. For each node until NULL:
	 *    a. If free_func is not NULL, call free_func(node->data) to free the data.
	 *    b. Save a pointer to the next node.
	 *    c. Free the current node.
	 *    d. Move to the next node.
	 * 3. After all nodes are freed, free the sentinel node (list->head).
	 * 4. Free the List structure itself.
	 */

    ListNode *current = list->head->next;
    while (current) {
        if (free_func) {
            free_func(current->data);
        }
        ListNode *next = current->next;
        free(current);
        current = next;
    }

    free(list->head);
    free(list);
}

// Assisted By AI
bool list_append(List *list, void *data) {
	/*
	 * PLAN for list_append:
	 * 1. Allocate a new ListNode.
	 *    - If allocation fails, return false.
	 * 2. Set the new node's data pointer to the provided data.
	 * 3. Set the new node's next pointer to NULL (since it will be the last node).
	 * 4. Traverse the list starting from the sentinel node (list->head)
	 *    until you reach the last node (whose next is NULL).
	 * 5. Set the last node's next pointer to the new node.
	 * 6. Increment the list's size field.
	 * 7. Return true to indicate success.
	 */

  ListNode *new_node = malloc(sizeof(ListNode));
  if (!new_node) {
    return false;
  }

  new_node->data = data;

  new_node->next = NULL;

  ListNode *current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new_node;

  list->size++;

  return true;
}

// Assisted By AI
bool list_insert(List *list, size_t index, void *data) {
	/*
	 * PLAN for list_insert:
	 * 1. Check index validity:
	 *    - If index > list->size, return false (out of bounds).
	 * 2. Allocate a new ListNode:
	 *    - If allocation fails, return false.
	 * 3. Set new node’s data and next pointer:
	 *    - new_node->data = data;
	 *    - new_node->next = NULL; (will be set properly in the next step)
	 * 4. Find the node before the insertion point:
	 *    - Start from the sentinel node (list->head).
	 *    - Traverse index times to reach the node just before the desired position.
	 * 5. Insert the new node:
	 *    - Set new_node->next to the next node of the previous node.
	 *    - Set the previous node’s next to the new node.
	 * 6. Increment the list’s size.
	 * 7. Return true to indicate success.
	 */

  if (index > list->size) {
      return false; // Out of bounds
  }

  ListNode *new_node = malloc(sizeof(ListNode));
  if (!new_node) {
      return false; // Allocation failed
  }

  new_node->data = data;
  new_node->next = NULL; // Will be set properly in the next step

  ListNode *prev = list->head;
  for (size_t i = 0; i < index; i++) {
      prev = prev->next;
  }

  new_node->next = prev->next;
  prev->next = new_node;

  list->size++;

  return true;
}

// Assisted By AI
void *list_remove(List *list, size_t index) {
	/*
	 * PLAN for list_remove:
	 * 1. Check index validity:
	 *    - If index >= list->size, return NULL (out of bounds).
	 * 2. Find the node before the one to remove:
	 *    - Start from the sentinel node (list->head).
	 *    - Traverse index times to reach the node just before the one to remove.
	 * 3. Remove the node:
	 *    - Save a pointer to the node to be removed (to_remove = prev->next).
	 *    - Save the data pointer from the node to be removed.
	 *    - Set prev->next to to_remove->next.
	 * 4. Free the removed node.
	 * 5. Decrement the list’s size.
	 * 6. Return the saved data pointer.
	 */

  if (index >= list->size) {
      return NULL; // Out of bounds
  }

  ListNode *prev = list->head;
  for (size_t i = 0; i < index; i++) {
      prev = prev->next;
  }

  ListNode *to_remove = prev->next;
  void *data = to_remove->data;

  prev->next = to_remove->next;

  free(to_remove);

  list->size--;

  return data;
}

// Assisted By AI
void *list_get(const List *list, size_t index) {
	/*
	 * PLAN for list_get:
	 * 1. Check if index is out of bounds (index >= list->size). If so, return NULL.
	 * 2. Start from the first real node (list->head->next).
	 * 3. Traverse the list index times to reach the desired node.
	 * 4. Return the data pointer from that node.
	 */
  if (index >= list->size) {
      return NULL; // Out of bounds
  }

  ListNode *current = list->head->next;
  for (size_t i = 0; i < index; i++) {
      current = current->next;
  }

  return current->data;
}

// Assisted By AI
size_t list_size(const List *list) {
	/*
	 * PLAN for list_size:
	 * 1. Return the size field from the List structure.
	 */
  return list->size;  
}

// Assisted By AI
bool list_is_empty(const List *list) {
	/*
	 * PLAN for list_is_empty:
	 * 1. Return true if the list's size field is 0, false otherwise.
	 */
  return list->size == 0;
}

