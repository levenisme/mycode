#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int findlargestIndex(int * array, int n) {
  if (n <= 0) {
    return -1;
  }
  int largestIndex = 0;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[largestIndex]) {
      largestIndex = i;
    }
  }
  return largestIndex;
}
char MostFrequent(FILE * f) {
  int alphabet[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      alphabet[c - 'a']++;
    }
  }
  int number = findlargestIndex(alphabet, 26);
  return number;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  int ans = MostFrequent(f) - 4;
  if (ans < 0) {
    ans = ans + 26;
  }
  printf("%d\n", ans);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
