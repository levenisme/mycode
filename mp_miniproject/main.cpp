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
    myShell.dirName = NULL;
    // std::string input_line;  //h
    getline(std::cin, myShell.input_line);
    //    std::cout << "inputline: " << myShell.input_line << std::endl;
    myShell.input_line = myShell.searchPath(myShell.input_line);  //verify if need to add path
    size_t findEqual = myShell.input_line.find('=', 0);
    //    std::cout << "find=:" << findEqual << std::endl;
    //std::cout << "inputline: " << myShell.input_line << std::endl;
    if (findEqual != std::string::npos) {  //step3.3 provide access to variables
      myShell.executeVal(myShell.input_line, findEqual);
      /* std::string key = myShell.input_line.substr(0, findEqual);
      std::string value = myShell.input_line.substr(findEqual + 1, myShell.input_line.size() - 1);
      std::cout << "key: " << key << std::endl;
      std::cout << "value: " << value << std::endl;*/
      // myShell.inputVal[key] = value;
    }
    else {
      if (std::cin.eof()) {
        exit(EXIT_SUCCESS);
      }
      else if (myShell.input_line == "exit") {
        myShell.charVec.clear();
        break;
        // exit(EXIT_SUCCESS);
      }

      //std::string getCd = getenv("HOME");//??????????remove?
      //  std::cout << "cdpath" << getCd << std::endl;
      else {
        std::vector<std::string> parseTemp;

        std::istringstream stringIn(myShell.input_line);

        std::string word;
        size_t findSlash = myShell.input_line.find('\\', 0);
        if (findSlash == std::string::npos) {
          //          std::cout << "not findslash" << std::endl;
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
        /* for (size_t i = 0; i < parseTemp.size(); i++) {
          std::cout << "checkparse" << i << ": " << parseTemp[i] << std::endl;
	  }*/
        //        std::cout << "parseTemp[0]:" << parseTemp[0] << std::endl;
        // std::cout << "parseTemp[0].compare():" << parseTemp[0].compare("echo") << std::endl;
        if ((parseTemp[0].compare("set") == 0 || parseTemp[0].compare("/bin/set") == 0) &&
            parseTemp.size() >= 3) {
          //          size_t positionS = (parseTemp[0]).size() + (parseTemp[1]).size();
          // myShell.executeVal(parseTemp[1].append(parseTemp[2]), positionS);
          myShell.executeSet(parseTemp[1], myShell.input_line, myShell.inputVal);
        }
        else if ((parseTemp[0].compare("echo") == 0) || (parseTemp[0].compare("/bin/echo") == 0)) {
          myShell.parseValue(myShell.inputVal, parseTemp);
        }
        else if (((parseTemp[0].compare("export") == 0) ||
                  (parseTemp[0].compare("/bin/export") == 0)) &&
                 (parseTemp.size() == 2)) {
          myShell.executeExport(myShell.inputVal, parseTemp);
        }
        else {
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
          // std::cout << "hello" << std::endl;
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

          /*    for (std::vector<char *>::iterator it = myShell.charVec.begin(); it != myShell.charVec.end();
         it++) {
      delete *it;
      *it = NULL;
      }*/

          for (size_t i = 0; i < myShell.charVec.size(); i++) {
            myShell.charVec.pop_back();
          }
          std::vector<char *>().swap(myShell.charVec);
          myShell.charVec.clear();
        }
      }
    }
  }
  // std::vector<char *>().swap(myShell.charVec);
  delete[] myShell.path;
  myShell.path = NULL;

  return EXIT_SUCCESS;
}
