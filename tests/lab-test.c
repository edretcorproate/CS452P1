#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"


void setUp(void) {
  printf("Setting up tests...\n");
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

// Removed test_add, test_subtract, test_get_greeting as they are not relevant to lab.h
// Added Tests for lab.h functions

// Assisted By AI
// Testing List Creation
void test_list_create(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(0, list_size(list));
  TEST_ASSERT_TRUE(list_is_empty(list));
  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List Destruction
void test_list_destroy(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *data1 = malloc(sizeof(int));
  int *data2 = malloc(sizeof(int));
  *data1 = 10;
  *data2 = 20;
  list_append(list, data1);
  list_append(list, data2);

  list_destroy(list, free); // Use free to deallocate int pointers
  // If we reach here without crashing, the test passes
  TEST_ASSERT_TRUE(true);
}

// Assisted By AI
// Testing List Append
void test_list_append(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10, b = 20, c = 30;
  list_append(list, &a);
  list_append(list, &b);
  list_append(list, &c);

  TEST_ASSERT_EQUAL(3, list_size(list));
  TEST_ASSERT_FALSE(list_is_empty(list));
  TEST_ASSERT_EQUAL_PTR(&a, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(&b, list_get(list, 1));
  TEST_ASSERT_EQUAL_PTR(&c, list_get(list, 2));

  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List Insertion
void test_list_insert(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10, b = 20, c = 30;
  list_append(list, &a);
  list_append(list, &c);
  list_insert(list, 1, &b); // Insert b between a and c

  TEST_ASSERT_EQUAL(3, list_size(list));
  TEST_ASSERT_EQUAL_PTR(&a, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(&b, list_get(list, 1));
  TEST_ASSERT_EQUAL_PTR(&c, list_get(list, 2));

  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List Removal
void test_list_remove(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10, b = 20, c = 30;
  list_append(list, &a);
  list_append(list, &b);
  list_append(list, &c);

  int *removed = (int *)list_remove(list, 1); // Remove b
  TEST_ASSERT_EQUAL_PTR(&b, removed);
  TEST_ASSERT_EQUAL(2, list_size(list));
  TEST_ASSERT_EQUAL_PTR(&a, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(&c, list_get(list, 1));

  // Do not free(removed) here to avoid double-free; let list_destroy handle it if needed
  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List GET
void test_list_get(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10, b = 20, c = 30;
  list_append(list, &a);
  list_append(list, &b);
  list_append(list, &c);

  TEST_ASSERT_EQUAL_PTR(&a, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(&b, list_get(list, 1));
  TEST_ASSERT_EQUAL_PTR(&c, list_get(list, 2));
  TEST_ASSERT_NULL(list_get(list, 3)); // Out of bounds

  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List Size
void test_list_size(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_EQUAL(0, list_size(list));

  int a = 10, b = 20;
  list_append(list, &a);
  TEST_ASSERT_EQUAL(1, list_size(list));

  list_append(list, &b);
  TEST_ASSERT_EQUAL(2, list_size(list));

  list_remove(list, 0);
  TEST_ASSERT_EQUAL(1, list_size(list));

  list_remove(list, 0);
  TEST_ASSERT_EQUAL(0, list_size(list));

  list_destroy(list, NULL);
}

// Assisted By AI
// Testing List is_empty
void test_list_is_empty(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_TRUE(list_is_empty(list));

  int a = 10;
  list_append(list, &a);
  TEST_ASSERT_FALSE(list_is_empty(list));

  list_remove(list, 0);
  TEST_ASSERT_TRUE(list_is_empty(list));

  list_destroy(list, NULL);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_list_create);
  RUN_TEST(test_list_destroy);
  RUN_TEST(test_list_append);
  RUN_TEST(test_list_insert);
  RUN_TEST(test_list_remove);
  RUN_TEST(test_list_get);
  RUN_TEST(test_list_size);
  RUN_TEST(test_list_is_empty);
  return UNITY_END();
}
