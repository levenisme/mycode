#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "myShell.h"
int main(void) {
  myShell myShell;
  while (1) {
    myShell.dirName = get_current_dir_name();
    std::cout << "myShell:" << myShell.dirName << " $";
    free(myShell.dirName);
    // std::string input_line;  //h
    getline(std::cin, myShell.input_line);
    std::cout << "inputline: " << myShell.input_line << std::endl;
    myShell.input_line = myShell.searchPath(myShell.input_line);  //verify if need to add path

    std::cout << "inputline: " << myShell.input_line << std::endl;
    if (std::cin.eof()) {
      exit(EXIT_SUCCESS);
    }
    if (myShell.input_line == "exit") {
      myShell.charVec.clear();
      exit(EXIT_SUCCESS);
    }

    //std::string getCd = getenv("HOME");//??????????remove?
    //  std::cout << "cdpath" << getCd << std::endl;

    std::vector<std::string> parseTemp;

    std::istringstream stringIn(myShell.input_line);

    std::string word;
    size_t findSlash = myShell.input_line.find('\\', 0);

    //std::cout << "findslash" << findSlash << std::endl;
    if (findSlash == std::string::npos) {
      while (stringIn >> word) {  //separate each
        parseTemp.push_back(word);
      }
    }
    else {
      while (std::getline(stringIn, word, ' ')) {
        parseTemp.push_back(word);
      }
    }
    parseTemp = myShell.checkParse(parseTemp);
    /*    for (size_t i = 0; i < parseTemp.size(); i++) {
      std::cout << "checkparse" << i << ": " << parseTemp[i] << std::endl;
      }*/

    //myShell.charVec(parseTemp.size(), nullptr);
    std::cout << "checkcharVecSize: " << myShell.charVec.size() << std::endl;
    for (size_t i = 0; i < parseTemp.size(); i++) {  //convert string into char*
      //  std::cout << "checkparse" << i << ": " << parseTemp[i].c_str() << std::endl;
      myShell.charVec.push_back((char *)parseTemp[i].c_str());
      // std::cout << "charVecPush" << i << ": " << myShell.charVec[i] << std::endl;
    }
    for (size_t i = 0; i < parseTemp.size(); i++) {
      std::cout << "checkcharVec" << i << ": " << myShell.charVec[i] << std::endl;
    }
    // charVec.push_back(NULL);
    //check if press enter
    if (myShell.charVec.size() == 0) {
      //      std::cout << "this is just return" << std::endl;
      continue;
    }
    std::cout << "hello" << std::endl;
    if (strcmp(myShell.charVec[0], "cd") == 0) {
      //      std::cout << "this is cd command" << std::endl;
      myShell.executeCd(myShell.charVec);  //execute cd
    }
    else {
      //std::cout << "hello" << std::endl;
      myShell.charVec.push_back(NULL);
      myShell.execution(myShell.charVec);  //execute normal commands
    }
    parseTemp.clear();

    for (std::vector<char *>::iterator it = myShell.charVec.begin(); it != myShell.charVec.end();
         it++) {
      delete *it;
      *it = NULL;
    }
    myShell.charVec.clear();
    //myShell.free(myShell.charVec);
  }
  // std::vector<char *>().swap(myShell.charVec);
  return EXIT_SUCCESS;
}
