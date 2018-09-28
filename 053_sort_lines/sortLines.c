#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort1(void) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap = 0;
  size_t i = 0;
  while (getline(&curr, &linecap, stdin) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s\n", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

void sort2(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s\n", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc < 1) {
    fprintf(stderr, "you need at least one input file\n");
    return EXIT_FAILURE;
  }

  else if (argc == 1) {
    sort1();
    return EXIT_SUCCESS;
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("could not open file");
        return EXIT_FAILURE;
      }
      sort2(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
