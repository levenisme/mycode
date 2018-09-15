// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
int seq3(int x, int y) {
  int seq3;
  seq3 = -3 * x + y * (x + 2);
  return seq3;
}
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int even = 0;
  if (xLow < xHi) {
    for (int i = xLow; i < xHi; i++) {
      for (int j = yLow; j < yHi; j++) {
        if (seq3(i, j) % 2 == 0) {
          even++;
        }
      }
    }
  }
  else {
    even = 0;
  }
  return even;
}
int main() {
  int x1 = -3;
  int x2 = -1;
  int x3 = 0;
  int x4 = 1;
  int x5 = 3;
  printf("seq3(%d,%d) = %d\n", x1, x1, seq3(x1, x1));
  printf("seq3(%d,%d) = %d\n", x1, x2, seq3(x1, x2));
  printf("seq3(%d,%d) = %d\n", x2, x3, seq3(x2, x3));
  printf("seq3(%d,%d) = %d\n", x2, x3, seq3(x3, x5));
  printf("seq3(%d,%d) = %d\n", x2, x3, seq3(x4, x5));

  int y1, y2, y3, y4, y5;
  y1 = -5;
  y2 = 5;
  y3 = 0;
  y4 = 4;
  y5 = -1;

  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y1,
         y2,
         y1,
         y2,
         countEvenInSeq3Range(y1, y2, y1, y2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y3,
         y4,
         y3,
         y4,
         countEvenInSeq3Range(y3, y4, y3, y4));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y1,
         y1,
         y2,
         y3,
         countEvenInSeq3Range(y1, y1, y2, y3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y1,
         y4,
         y1,
         y4,
         countEvenInSeq3Range(y1, y4, y1, y4));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y2,
         y5,
         y3,
         y4,
         countEvenInSeq3Range(y2, y5, y3, y4));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         y2,
         y3,
         y4,
         y5,
         countEvenInSeq3Range(y2, y3, y4, y5));
  return 0;
}
