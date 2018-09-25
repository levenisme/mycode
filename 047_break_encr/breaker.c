#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int sort(int * array) {
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (max < array[i]) {
      max = i;
    }
  }
  return max;
}
char MostFrequent(FILE * f) {
  int alphabet[27];
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      alphabet[c - 97]++;
    }
  }
  int number = sort(alphabet);
  return ('a' + number);
}
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int key;
  FILE * f = fopen(argv[2], "r");
  key = MostFrequent(f) - 'e';
  printf("%d", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
