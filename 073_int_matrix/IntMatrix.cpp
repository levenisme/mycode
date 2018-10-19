#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++) {
    {
      rows[i] = new IntArray(rhs[i]);
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = new IntArray *[numRows]();
    for (int i = 0; i < numRows; i++) {
      rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  bool check = 1;
  if (numColumns != rhs.numColumns) {
    check = 0;
  }
  if (numRows != rhs.numRows) {
    check = 0;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i])
      check = 0;
  }
  return check;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix sum = IntMatrix(*this);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*sum.rows[i])[j] += (*rhs.rows[i])[j];
    }
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  int numr = rhs.getRows();
  for (int i = 0; i < numr; i++) {
    s << rhs[i];
    if (i != numr - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
