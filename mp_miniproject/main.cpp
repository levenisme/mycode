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
    myShell.dirName = get_current_dir_name();            //get current dir
    std::cout << "myShell:" << myShell.dirName << " $";  //outout current dir
    free(myShell.dirName);  //get_current_dir_name will create new space, free it in this step
    myShell.dirName = NULL;
    if (std::cin.eof()) {  //if enter ^d, exit

      break;
    }
    getline(std::cin, myShell.input_line);  //get the input line
    if (myShell.input_line.size() == 0) {   //if just type enter
      continue;
    }

    if (myShell.input_line == "exit") {
      break;
    }

    size_t findCorrectStart = myShell.input_line.find_first_not_of(' ', 0);
    if (findCorrectStart == std::string::npos) {  //if type spaces and enter
      continue;
    }
    //remove the spaces before command to get right input
    myShell.input_line = myShell.input_line.substr(findCorrectStart, myShell.input_line.size());
    /*    if (findCorrectStart == std::string::npos) {  //if just type enter
      continue;
      }*/

    myShell.input_line = myShell.searchPath(myShell.input_line);  //verify if need to add path
    //    if ((myShell.input_line.compare("notFind")) == 0) {
    // continue;
    // }
    size_t findEqual = myShell.input_line.find('=', 0);  //if it has '=', it should access the val
    if (myShell.input_line.size() == 0) {                //if the input is enter
      continue;
    }
    else if (findEqual != std::string::npos) {  //step3.3 provide access to variables
      myShell.executeVal(myShell.input_line, findEqual);
    }
    else {
      std::vector<std::string> parseTemp;

      parseTemp = myShell.checkParse(parseTemp);
      std::istringstream stringIn(myShell.input_line);

      std::string word;
      size_t findSlash = myShell.input_line.find('\\', 0);  //if find a seperator
      if (findSlash == std::string::npos) {
        while (stringIn >> word) {  //separate each in a normal way
          parseTemp.push_back(word);
        }
      }

      else {
        while (std::getline(stringIn, word, ' ')) {  //if find a seperator, ./myProgram a\  b c \ d
          parseTemp.push_back(word);
        }
      }
      parseTemp = myShell.checkParse(parseTemp);  //ignore the slash in the input
      if ((parseTemp[0].compare("set") == 0 || parseTemp[0].compare("/bin/set") == 0) &&
          parseTemp.size() >= 3) {
        myShell.executeSet(
            parseTemp[1], myShell.input_line, myShell.inputVal);  //execute the set command
      }
      else if ((parseTemp[0].compare("echo") == 0) || (parseTemp[0].compare("/bin/echo") == 0)) {
        myShell.parseValue(myShell.inputVal, parseTemp);  //execute echo command
      }
      else if (((parseTemp[0].compare("export") == 0) ||
                (parseTemp[0].compare("/bin/export") == 0)) &&
               (parseTemp.size() == 2)) {
        myShell.executeExport(myShell.inputVal, parseTemp);  //execute export command
      }
      else if (((parseTemp[0].compare("inc") == 0) || (parseTemp[0].compare("/bin/inc") == 0)) &&
               (parseTemp.size() == 2)) {
        myShell.excuteInc(myShell.inputVal, parseTemp[1]);  //execute inc command
      }
      else {                                             //
        for (size_t i = 0; i < parseTemp.size(); i++) {  //convert string into char*
          myShell.charVec.push_back((char *)parseTemp[i].c_str());
        }
        if (myShell.charVec.size() == 0) {
          continue;
        }
        if (strcmp(myShell.charVec[0], "cd") == 0) {
          myShell.executeCd(myShell.charVec);  //execute cd command
        }

        else {
          myShell.charVec.push_back(NULL);
          extern char ** environ;
          myShell.execution(myShell.input_line, myShell.charVec, environ);  //execute normal command
        }
        parseTemp.clear();
        std::vector<char *>().swap(myShell.charVec);  //free memory
        myShell.charVec.clear();
      }
    }
  }
  //  delete[] myShell.path;
  // myShell.path = NULL;
  return EXIT_SUCCESS;
}
