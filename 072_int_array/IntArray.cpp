#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : numElements(n) {
  data = new int[numElements];
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
IntArray::~IntArray() {
  delete[] data;
  data = NULL;
}
const int & IntArray::operator[](int index) const {
  return data[index];
}
int & IntArray::operator[](int index) {
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  bool check = 1;
  if (numElements != rhs.numElements)
    check = 0;
  for (int i = 0; i < numElements; i++) {
    if (rhs.data[i] != data[i]) {
      check = 0;
    }
  }
  return check;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  bool check = 0;
  if (numElements != rhs.numElements)
    check = 1;
  for (int i = 0; i < numElements; i++) {
    if (rhs.data[i] != data[i]) {
      check = 1;
    }
  }
  return check;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  int length = rhs.size();
  for (int i = 0; i < length; i++) {
    s << rhs[i];
    if (i != length - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
