#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, size_t expected_ans) {
  size_t ans;
  ans = maxSeq(array, n);
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}
int main() {
  int array1[] = {
      1,
      2,
      3,
      4,
      5,
  };
  int array2[] = {-1, -1, -1, -1};
  int array3[] = {-2, -2, -1, 0, 1, 2};
  int array4[] = {0, 0, 0, 0, 0};
  int array5[] = {4, 3, 2, 1, -5};
  int array6[] = {};
  int array7[] = {1, -2, 3, -4, 0};
  run_check(array1, 5, 5);
  run_check(array2, 4, 1);
  run_check(array3, 6, 5);
  run_check(array4, 5, 1);
  run_check(array5, 5, 1);
  run_check(array6, 0, 0);
  run_check(array7, 5, 2);
  return EXIT_SUCCESS;
}
