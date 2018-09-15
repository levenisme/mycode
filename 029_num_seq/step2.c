// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>

int seq2(int x) {
  int seq2;
  seq2 = x * x + 3 * x + 1;
  return seq2;
}
int sumSeq2(int low, int high) {
  int sum = 0;
  if (low <= high) {
    for (int i = low; i < high; i++) {
      int seq2i = seq2(i);
      sum = sum + seq2i;
    }
  }
  else {
    sum = 0;
  }
  return sum;
}

int main() {
  int x1 = -2;
  int x2 = 0;
  int x3 = 3;
  seq2(x1);
  seq2(x2);
  seq2(x3);
  printf("seq2(%d) = %d\n", x1, seq2(x1));
  printf("seq2(%d) = %d\n", x2, seq2(x2));
  printf("seq2(%d) = %d\n", x3, seq2(x3));

  int y1, y2, y3, y4, y5, y6;
  y1 = 0;
  y2 = 2;
  y3 = 3;
  y4 = 6;
  y5 = 9;
  y6 = 7;
  printf("sumSeq2(%d, %d) = %d\n", y1, y2, sumSeq2(y1, y2));
  printf("sumSeq2(%d, %d) = %d\n", y3, y4, sumSeq2(y3, y4));
  printf("sumSeq2(%d, %d) = %d\n", y5, y6, sumSeq2(y5, y6));
  printf("sumSeq2(%d, %d) = %d\n", y1, y3, sumSeq2(y1, y3));
  printf("sumSeq2(%d, %d) = %d\n", y2, y2, sumSeq2(y2, y2));
  printf("sumSeq2(%d, %d) = %d\n", y1, y6, sumSeq2(y1, y6));

  return 0;
}
