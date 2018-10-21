#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
void printout(std::vector<std::string> & strvec) {
  std::vector<std::string>::iterator it = strvec.begin();
  while (it != strvec.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}
void sortcin() {
  std::vector<std::string> strvec;  //use vector to hold array
  std::string s;
  while (std::getline(std::cin, s)) {
    strvec.push_back(s);
  }
  sort(strvec.begin(), strvec.end());
  printout(strvec);
}
void readfile(std::ifstream & input) {
  std::vector<std::string> strvec;  //use vector to hold array
  std::string s;
  while (std::getline(input, s)) {
    strvec.push_back(s);
  }
  sort(strvec.begin(), strvec.end());
  printout(strvec);
}

int main(int argc, char ** argv) {
  std::ifstream input;

  if (argc == 1) {
    sortcin();
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      input.open(argv[i]);
      if (input.is_open()) {
        readfile(input);
        input.close();
      }
      else {
        perror("fail to open file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
