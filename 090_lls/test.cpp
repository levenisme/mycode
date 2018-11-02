#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.h"

int main(void) {
  LinkedList<int> list1;
  list1.addFront(1);
  assert(list1.getSize() == 0);
  std::cout << "success"
            << "\n";
}
