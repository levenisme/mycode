#include <assert.h>

#include <cstdlib>

#include "il.h"
void testList(void) {
  IntList list;
  assert(list.getSize() == 0 && list.head == NULL && list.tail == NULL);
  list.addFront(1);
  assert(list.find(1) == 0);
  assert(list.getSize() == 1);
  list.addFront(1);
  assert(list.find(1) == 0);
  assert(list.getSize() == 2);
  list.addBack(2);
  assert(list.find(2) == 2);
  assert(list.getSize() == 3);
  list.addBack(3);
  assert(list.find(3) == 3);
  list.remove(3);
  list.addBack(4);
  assert(list.find(4) == 3);  //add and remove
  assert(list[3] == 4);       //find
  IntList list2;              //copy
  list2 = list;
  assert(list2.getSize() == 4);
  assert(list2[2] == 2);
  assert(list2.find(1) == 0);
  IntList list3;  //operator
  list3.addFront(1);
  list3 = list;
  list3 = list;
  assert(list3.getSize() == 4);
  assert(list3[2] == 2);
  assert(list3.find(1) == 0);
  list3.remove(1);
  list3.remove(2);
  list3.remove(4);
  assert(list3.getSize() == 1);
  assert(list3[0] == 1);
  list3.remove(1);
  assert(list3.getSize() == 0);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
