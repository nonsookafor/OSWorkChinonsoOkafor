#include <stdio.h>

#include "list.h"

void testListAlloc() {
  list_t* myList = list_alloc();
  node_t* curr = myList->head;
  while (curr != NULL) {
    printf("%d\n", curr->value);
    curr = curr->next;
  }
  printf("1. Finished listAlloc\n\n");
}

void testFreeList(){
  printf("2. Finished listFree\n\n");
}

void testAddToBack() {
  list_t* myList3 = list_alloc();
  list_add_to_back(myList3, 1);
  list_add_to_back(myList3, 2);
  node_t* curr = myList3->head;
  while (curr != NULL) {
    printf("%d\n", curr->value);
    curr = curr->next;
  }
  printf("3. Finished listAddToBack\n\n");
}

void testAddToFront() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_front(myList4, 6);
  list_add_to_front(myList4, 7);
  node_t* curr = myList4->head;
  while (curr != NULL) {
    printf("%d\n", curr->value);
    curr = curr->next;
  }
  printf("4. Finished listAddToFront\n\n");
}

void testGetLength() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_front(myList4, 6);
  list_add_to_front(myList4, 7);
  list_length(myList4);
  printf("5. Finished listAddToFront\n\n");
}

void testPrintElements() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 5);
  list_add_to_back(myList4, 6);
  list_add_to_front(myList4, 4);
  list_add_to_front(myList4, 3);
  list_print(myList4);
  printf("6. Finished printNodes\n\n");
}

void testListAddAtIndex() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_add_at_index(myList4, 45, 0);
  list_print(myList4);
  printf("7. Finished listAddAtIndex\n\n");
}

void testRemoveFromBack() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_remove_from_back(myList4);
  list_print(myList4);
  printf("8. Finished listRemoveFromBack\n\n");
}

void testRemoveFromFront() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_remove_from_front(myList4);
  list_print(myList4);
  printf("9. Finished listRemoveFromFront\n\n");
}

void testRemoveWithIndex() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_remove_at_index(myList4, 0);
  list_print(myList4);
  printf("10. Finished listRemoveAtIndex\n\n");
}

void testListIsIn() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_is_in(myList4, 7);
  printf("11. Finished listIsIn\n\n");
}

void testGetElement() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_get_elem_at(myList4, 0);
  printf("12. Finished listGetElement\n\n");
}

void testGetIndex() {
  list_t* myList4 = list_alloc();
  list_add_to_back(myList4, 1);
  list_add_to_back(myList4, 2);
  list_add_to_back(myList4, 3);
  list_add_to_back(myList4, 4);
  list_get_index_of(myList4, 4);
  printf("13. Finished listGetIndex\n\n");
}


int main() {
  printf("Tests for linked list implementation\n\n");
	testListAlloc();
  testFreeList();
  testAddToBack();
  testAddToFront();
  testGetLength();
  testPrintElements();
  testListAddAtIndex();
  testRemoveFromBack();
  testRemoveFromFront();
  testRemoveWithIndex();
  testListIsIn();
  testGetElement();
  testGetIndex();
  return 0;
}
