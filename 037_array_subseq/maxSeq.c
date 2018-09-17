#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t max, temp;
  max = temp = 1;

  if (array == NULL || n == 0) {
    return 0;
  }
  else if (n == 1) {
    return 1;
  }
  else {
    for (size_t i = 0; i < n - 1; i++) {
      if (array[i] < array[i + 1]) {
        temp++;
        if (max < temp) {
          max = temp;
        }
        else {
        };
      }
      else
        temp = 1;
    }
  }

  return max;
}
