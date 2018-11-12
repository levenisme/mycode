#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream inFile;

  inFile.open(fname);
  if (!inFile) {
    perror("fail to open");
    exit(EXIT_FAILURE);
  }
  uint64_t * arr = new uint64_t[257]();
  int in = 0;
  while ((in = inFile.get()) != EOF) {
    arr[in]++;
  }
  arr[256] = 1;
  inFile.close();
  return arr;

  //WRITE ME!
}
