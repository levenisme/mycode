// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
int seq1(int x) {
  int seq1;
  seq1 = 4 * x - 3;
  return seq1;
}
void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high; i++) {
      if (i < high - 1) {
        printf("%d, ", seq1(i));
      }
      else {
        printf("%d\n", seq1(i));
      }
    }
  }
}

int main() {
  int x1 = -2;
  int x2 = 0;
  int x3 = 3;
  seq1(x1);
  seq1(x2);
  seq1(x3);
  printf("seq1(%d) = %d\n", x1, seq1(x1));
  printf("seq1(%d) = %d\n", x2, seq1(x2));
  printf("seq1(%d) = %d\n", x3, seq1(x3));

  int y1, y2, y3, y4, y5;
  y1 = -4;
  y2 = 1;
  y3 = 0;
  y4 = -1;
  y5 = 5;
  printf("printSeq1Range(%d,%d)\n", y1, y2);
  printSeq1Range(y1, y2);
  printf("printSeq1Range(%d,%d)\n", y1, y1);
  printSeq1Range(y1, y1);
  printf("printSeq1Range(%d,%d)\n", y1, y3);
  printSeq1Range(y1, y3);
  printf("printSeq1Range(%d,%d)\n", y2, y4);
  printSeq1Range(y2, y4);
  printf("printSeq1Range(%d,%d)\n", y4, y5);
  printSeq1Range(y4, y5);
  return 0;
}
