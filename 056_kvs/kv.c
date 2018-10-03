#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
kvpair_t * findPair(FILE * f) {
  kvpair_t * pr = malloc(sizeof(*pr));
  size_t sz = 0;
  pr->key = NULL;
  char * p = NULL;
  if (getline(&p, &sz, f) != -1) {
    //(*len)++;
    //printf("%d", *len);
    char * pequal = strchr(p, '=');
    char * pend = strchr(p, '\n');
    pr->key = strndup(p, pequal - p);
    pr->value = strndup(pequal + 1, pend - pequal - 1);
    //free getline
    free(p);
    p = NULL;
    return pr;
  }
  free(p);
  free(pr);
  return NULL;
}

kvarray_t * readKVs(const char * fname) {
  FILE * kv = fopen(fname, "r");
  if (kv == NULL) {
    perror("could not open file");
    exit(EXIT_FAILURE);
  }
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->array = NULL;
  ans->length = 0;

  int i = 0;
  kvpair_t * pr = NULL;
  while ((pr = findPair(kv)) != NULL) {
    ans->length++;
    ans->array = realloc(ans->array, (ans->length) * sizeof(*ans->array));
    if (ans->array == NULL) {
      perror("realloc fails");
      exit(EXIT_FAILURE);
    }
    ans->array[i++] = pr;
  }

  int resultC = fclose(kv);
  if (resultC != 0) {
    perror("failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return ans;

  //WRITE ME
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  char * ptr = NULL;
  for (int i = 0; i < pairs->length; i++) {
    if ((strcmp(pairs->array[i]->key, key)) == 0) {
      ptr = pairs->array[i]->value;
      return ptr;
    }
  }
  return ptr;
  //WRITE ME
}
