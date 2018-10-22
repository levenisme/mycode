#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) { rows.clear(); }
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    if (r < 0)
      numRows = 0;
    rows.resize(r);  //
    for (int i = 0; i < numRows; i++) {
      rows[i].resize(c);  //
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows.resize(numRows);
    for (int i = 0; i < numRows; i++) {
      {
        rows[i].resize(numColumns);
        rows[i] = rhs.rows[i];
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      rows[i].clear();
    }
    rows.clear();
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      for (int i = 0; i < numRows; i++) {
        rows[i].clear();
      }
      rows.clear();  //take care of ()
      numColumns = rhs.numColumns;
      numRows = rhs.numRows;
      rows.resize(numRows);
      for (int i = 0; i < numRows; i++) {
        rows[i].resize(numColumns);
        rows[i] = rhs.rows[i];  //take care of how to use,need two steps
      }
    }
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    bool check = 1;
    if (numColumns != rhs.numColumns) {
      check = 0;
    }
    if (numRows != rhs.numRows) {
      check = 0;
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != rhs.rows[i])
        check = 0;
    }
    return check;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix sum = Matrix(*this);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (sum.rows[i])[j] += (rhs.rows[i])[j];
      }
    }
    return sum;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
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
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
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

//YOUR CODE GOES HERE!

#endif
