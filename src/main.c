#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "lab.h"

#define MAX_STR_LEN 16

typedef struct {
    List *list;
    size_t start;
    size_t end;
    CompareFunc cmp;
} ThreadArg;

// Thread function for sorting a sublist
void *thread_sort(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    sort(targ->list, targ->start, targ->end, targ->cmp);
    return NULL;
}

// Generate a random string of length [min_len, max_len]
char *rand_str(int min_len, int max_len) {
    int len = min_len + rand() % (max_len - min_len + 1);
    char *s = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        s[i] = 'a' + rand() % 26;
    }
    s[len] = '\0';
    return s;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <int|string> <length>\n", argv[0]);
        return 1;
    }
    srand((unsigned)time(NULL));
    int is_int = strcmp(argv[1], "int") == 0;
    int is_str = strcmp(argv[1], "string") == 0;
    if (!is_int && !is_str) {
        printf("First argument must be 'int' or 'string'\n");
        return 1;
    }
    int n = atoi(argv[2]);
    if (n <= 0) {
        printf("Length must be positive integer\n");
        return 1;
    }
    // Allocate and fill data
    int *arr = NULL;
    char **sarr = NULL;
    if (is_int) {
        arr = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
    } else {
        sarr = malloc(n * sizeof(char *));
        for (int i = 0; i < n; i++) sarr[i] = rand_str(5, 15);
    }
    // Split into two sublists
    size_t mid = n / 2;
    List *l1 = list_create(LIST_LINKED_SENTINEL);
    List *l2 = list_create(LIST_LINKED_SENTINEL);
    if (is_int) {
        for (size_t i = 0; i < mid; i++) list_append(l1, &arr[i]);
        for (size_t i = mid; i < (size_t)n; i++) list_append(l2, &arr[i]);
    } else {
        for (size_t i = 0; i < mid; i++) list_append(l1, &sarr[i]);
        for (size_t i = mid; i < (size_t)n; i++) list_append(l2, &sarr[i]);
    }
    // Sort each sublist in a thread
    pthread_t t1, t2;
    ThreadArg arg1 = {l1, 0, list_size(l1), is_int ? compare_int : compare_str};
    ThreadArg arg2 = {l2, 0, list_size(l2), is_int ? compare_int : compare_str};
    pthread_create(&t1, NULL, thread_sort, &arg1);
    pthread_create(&t2, NULL, thread_sort, &arg2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    // Merge
    List *merged = merge(l1, l2, is_int ? compare_int : compare_str);
    // Output merged list (should be n elements)
    printf("Sorted list:\n");
    for (size_t i = 0; i < list_size(merged); i++) {
        if (is_int) {
            int *v = (int *)list_get(merged, i);
            printf("%d ", *v);
        } else {
            char **s = (char **)list_get(merged, i);
            printf("%s ", *s);
        }
    }
    printf("\n");
    // Verify
    if (is_sorted(merged, is_int ? compare_int : compare_str)) {
        printf("List is sorted!\n");
    } else {
        printf("List is NOT sorted!\n");
    }
    // Cleanup: only free original allocations
    if (is_int) {
        free(arr);
    } else {
        for (int i = 0; i < n; i++) free(sarr[i]);
        free(sarr);
    }
    list_destroy(l1, NULL);
    list_destroy(l2, NULL);
    list_destroy(merged, NULL);
    return 0;
}
