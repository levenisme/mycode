#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * pr = malloc(sizeof(*pr));
  pr->array = NULL;
  pr->length = 0;
  pr->u_count = 0;
  return pr;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  int check = 0;
  if (name == NULL) {
    c->u_count++;
  }
  else {
    for (int i = 0; i < c->length; i++) {
      if ((strcmp(c->array[i]->str, name)) == 0) {
        c->array[i]->count++;
        check = 1;
      }
    }
    if (check == 0) {
      c->length++;
      c->array = realloc(c->array, c->length * sizeof(*c->array));
      one_count_t * newone = malloc(sizeof(*newone));
      c->array[c->length - 1] = newone;
      c->array[c->length - 1]->str = name;
      c->array[c->length - 1]->count++;
    }
  }

  //WRITE ME
}
void printCounts(counts_t * c, FILE * outFile) {
  if (outFile == NULL) {
    perror("could not write the file");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < c->length; i++) {
    fprintf(outFile, "%s:%d\n", c->array[i]->str, c->array[i]->count);
  }
  fprintf(outFile, "<unknown>:%d\n", c->u_count);  //WRITE ME
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->length; i++) {
    free(c->array[i]);
  }
  free(c->array);
  free(c);
  //WRITE ME
}
