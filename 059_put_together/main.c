#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("invalid input");
    exit(EXIT_FAILURE);
  }
  char * line_p = NULL;
  size_t n = 0;
  counts_t * count = createCounts();
  while (getline(&line_p, &n, f) != EOF) {
    size_t length = strlen(line_p);  //\n
    line_p[length - 1] = '\0';
    char * val = lookupValue(kvPairs, line_p);
    addCount(count, val);
    //    n = 0;
  }
  //WRITE ME
  free(line_p);
  if (fclose(f) != 0) {
    perror("Fail to close the input file");
    exit(EXIT_FAILURE);
  }
  return count;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    perror("invalid input");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    //   (call this result c)
    char * outName = computeOutputFileName(argv[i]);
    //compute the output file name from argv[i] (call this outName)
    FILE * f = fopen(outName, "w");
    //open the file named by outName (call that f)
    printCounts(c, f);
    //print the counts from c into the FILE f
    if (fclose(f) != 0) {
      perror("Fail to close the input file");
      return EXIT_FAILURE;
    }
    //close f

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
