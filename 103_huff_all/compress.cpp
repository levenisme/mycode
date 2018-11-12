#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream input;
  input.open(inFile);
  int c;
  if (input.fail()) {
    perror("fail to open file");
    exit(EXIT_FAILURE);
  }
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  std::map<unsigned, BitString>::const_iterator it;
  while ((c = input.get()) != EOF) {
    it = theMap.find((unsigned)c);
    assert(it != theMap.end());
    bfw.writeBitString(it->second);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  it = theMap.find(256);
  //BitFileWriter will close the output file in its destructor
  bfw.writeBitString(it->second);
  //but you probably need to close your input file.
  input.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree(counts);
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString null;
  tree->buildMap(null, theMap);
  delete tree;

  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  return EXIT_SUCCESS;
}
