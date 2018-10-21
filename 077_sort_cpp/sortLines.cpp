#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
int main() {
  std::vector<std::string> strvec;  //use vector to hold array
  std::string s;
  while (std::cin >> s) {
    strvec.push_back(s);
  }
  sort(strvec.begin(), strvec.end());
  std::vector<std::string>::iterator it = strvec.begin();
  while (it != strvec.end()) {
    std::cout << *it << "\n";
    ++it;
  }
  return EXIT_SUCCESS;
}
