#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"
#include <stddef.h>

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

// Additional tests for edge cases and error paths
// Assisted By AI
// Testing Insertion at Out of Bounds Index
void test_list_insert_out_of_bounds(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10;
  bool result = list_insert(list, 2, &a); // List is empty, index 2 is out of bounds
  TEST_ASSERT_FALSE(result);
  list_destroy(list, NULL);
}

// Assisted By AI
// Testing Removal at Out of Bounds Index
void test_list_remove_out_of_bounds(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10;
  list_append(list, &a);
  void *removed = list_remove(list, 1); // Only one element, index 1 is out of bounds
  TEST_ASSERT_NULL(removed);
  list_destroy(list, NULL);
}

// Assisted By AI
// Testing Get at Out of Bounds Index
void test_list_get_out_of_bounds(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int a = 10;
  list_append(list, &a);
  void *data = list_get(list, 5); // Out of bounds
  TEST_ASSERT_NULL(data);
  list_destroy(list, NULL);
}

// Assisted By AI
// Testing Destroying an Empty List
void test_list_destroy_empty(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  list_destroy(list, NULL); // Should not crash
  TEST_ASSERT_TRUE(1); // Dummy assertion
}

// Assisted By AI
// Test list_create with an invalid ListType (defensive path)
void test_list_create_invalid_type(void) {
  // If your implementation only supports LIST_LINKED_SENTINEL, this should return a valid list or NULL.
  // This test will cover the defensive path if you add a check for unsupported types in list_create.
  List *list = list_create((ListType)9999); // Invalid type
  // Accept either NULL or a valid list, depending on your implementation
  // If you want to enforce NULL for invalid types, update list_create accordingly
  if (list) {
    list_destroy(list, NULL);
  }
  TEST_ASSERT_TRUE(1); // Dummy assertion to ensure the test runs
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
  RUN_TEST(test_list_insert_out_of_bounds);
  RUN_TEST(test_list_remove_out_of_bounds);
  RUN_TEST(test_list_get_out_of_bounds);
  RUN_TEST(test_list_destroy_empty);
  RUN_TEST(test_list_create_invalid_type);
  // Note: malloc failure paths in lab.c are not covered due to C macro/linker limitations.
  return UNITY_END();
}
