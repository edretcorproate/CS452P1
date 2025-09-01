#include "lab.h"
#include <stdio.h>

#ifdef TEST
#define main main_exclude
#endif



int main(void)
{
    // Test list_create
    List *list = list_create(LIST_LINKED_SENTINEL);
    printf("Created list.\n");

    // Test list_is_empty (should be true)
    printf("List is empty: %s\n", list_is_empty(list) ? "true" : "false");

    // Test list_append
    int a = 10, b = 20, c = 30;
    list_append(list, &a);
    list_append(list, &b);
    list_append(list, &c);
    printf("Appended 3 elements.\n");

    // Test list_size (should be 3)
    printf("List size: %zu\n", list_size(list));

    // Test list_is_empty (should be false)
    printf("List is empty: %s\n", list_is_empty(list) ? "true" : "false");

    // Test list_get
    int *val0 = (int *)list_get(list, 0);
    int *val1 = (int *)list_get(list, 1);
    int *val2 = (int *)list_get(list, 2);
    printf("Element at index 0: %d\n", val0 ? *val0 : -1);
    printf("Element at index 1: %d\n", val1 ? *val1 : -1);
    printf("Element at index 2: %d\n", val2 ? *val2 : -1);

    // Test list_insert (insert at index 1)
    int d = 15;
    list_insert(list, 1, &d);
    printf("Inserted 15 at index 1.\n");
    int *val1b = (int *)list_get(list, 1);
    printf("Element at index 1 after insert: %d\n", val1b ? *val1b : -1);

    // Test list_remove (remove at index 2)
    int *removed = (int *)list_remove(list, 2);
    printf("Removed element at index 2: %d\n", removed ? *removed : -1);
    printf("List size after remove: %zu\n", list_size(list));

    // Test list_destroy
    list_destroy(list, NULL); // No need to free ints
    printf("Destroyed list.\n");

    return 0;
}