#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans;
  ans = power(x, y);
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}
int main() {
  run_check(2, 4, 16);
  run_check(1, 0, 1);
  run_check(1, 1, 1);
  run_check(0, 0, 1);
  run_check(1, -1, 1);
  run_check(-2, 2, 4);
  run_check(-1, 3, -1);
  return (EXIT_SUCCESS);
}
