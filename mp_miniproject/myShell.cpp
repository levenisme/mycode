#include "myShell.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
myShell::myShell() : path(NULL), dirName(NULL), charVec(0, nullptr) {}
/*void myShell::free(std::vector<char *> & input) {
  for (std::vector<char *>::iterator it = input.begin(); it != input.end(); it++) {
    delete *it;
    *it = NULL;
  }
  input.clear();
  }*/
void myShell::executeCd(std::vector<char *> & cdArg) {
  /*  for (size_t i = 0; i < cdArg.size(); i++) {
    std::cout << i << " :" << cdArg[i] << "\n";
    std::cout << "size: " << cdArg.size() << std::endl;
    }*/
  if (cdArg.size() > 2) {
    std::cout << "size" << cdArg.size() << std::endl;
    perror("wrong cd arguments");
    return;
  }
  // std::cout << "cd path: " << cdArg[1] << std::endl;
  char * cdPath = cdArg[1];  //the input path
  chdir(cdPath);
}
//step2.2 if input has backslash

std::vector<std::string> myShell::checkParse(std::vector<std::string> & parse) {
  std::vector<std::string> checkParse;
  std::string temp;

  for (size_t i = 0; i < parse.size(); i++) {
    if (parse[i].back() == '\\') {
      temp = parse[i];
      //      std::cout << "have a \\temp value:" << temp << "i: " << i << std::endl;
      //  temp.erase(std::find(temp.begin(), temp.end(), '\\'));
      temp.push_back(' ');
      temp.append(parse[++i]);
      if (temp.back() == '\\') {
        temp.push_back(' ');
        temp.append(parse[++i]);
        temp.erase(std::find(temp.begin(), temp.end(), '\\'));
      }
      temp.erase(std::find(temp.begin(), temp.end(), '\\'));

      checkParse.push_back(temp);
    }
    else {
      //  std::cout << "have a normal  value:" << parse[i] << "i: " << i << std::endl;
      std::string temp2 = parse[i];
      // std::cout << "have a normal  value:" << parse[i] << "i: " << i << std::endl;
      size_t find = temp2.find('\\');
      if (find != std::string::npos) {
        temp2.erase(std::find(temp2.begin(), temp2.end(), '\\'));
      }
      checkParse.push_back(temp2);
    }
  }
  parse.clear();
  return checkParse;
}
//step2.1
//parse the path first, then find the right one and execute
std::vector<std::string> myShell::parsePath(char * path) {
  std::istringstream temp(path);
  std::string pathtemp;
  std::vector<std::string> parse;
  while (std::getline(temp, pathtemp, ':')) {
    parse.push_back(pathtemp);
  }
  return parse;
}
std::string myShell::executePath(std::vector<std::string> parseP, std::string input_line) {
  DIR * curr_dir;
  struct dirent * ent;
  std::string path;  //maybe use in the space
  //  std::cout << "input" << input_line << std::endl;
  std::string inputArg;
  size_t n = input_line.find(" ");
  inputArg = input_line.substr(0, n);
  // std::cout << "inputarg  " << inputArg << std::endl;
  std::vector<std::string>::iterator it = parseP.begin();
  while (it != parseP.end()) {
    curr_dir = opendir((*it).c_str());
    if (curr_dir == NULL) {
      perror("Could not open directory!");
      closedir(curr_dir);
      exit(EXIT_FAILURE);
    }
    else {
      while ((ent = readdir(curr_dir)) != NULL) {
        std::string file_name(ent->d_name);

        if (file_name == "." || file_name == "..") {
          continue;
        }

        else {
          if (inputArg.compare(file_name) == 0) {
            path = (*it) + "/" + input_line;
            //            std::cout << "if enter true" << path << std::endl;
            closedir(curr_dir);

            return path;
          }
        }
      }
      closedir(curr_dir);
    }
    ++it;
  }
  // std::cout << "if enter false" << input_line << "wrong" << path << std::endl;
  // std::vector<std::string>().swap(parseP);
  // parseP.clear();
  return input_line;  //cannot find path
}
//colon-delimited parse
std::string myShell::searchPath(std::string input_line) {
  const char * pathSig = "PATH";
  //char * path = NULL;
  path = getenv(pathSig);  //use the var
  std::vector<std::string> parseP = parsePath(path);
  /* for (size_t i = 0; i < parseP.size(); i++) {
    std::cout << parseP[i] << "\n";
    }*/
  std::string search;
  search = executePath(parseP, input_line);
  std::vector<std::string>().swap(parseP);
  parseP.clear();

  path = NULL;
  return search;
}

void myShell::execution(std::vector<char *> & input_line) {
  /*  //if type exit,maybe wrong place
  if (strcmp(input_line[0], "exit") == 0) {
    exit(EXIT_SUCCESS);
    }*/
  pid_t childPid = fork();
  char * envi[] = {NULL};
  int status;
  if (childPid == -1) {
    perror("cannot execute");
    exit(EXIT_FAILURE);
  }
  else if (childPid == 0) {
    /*    for (size_t i = 0; i < input_line.size(); i++) {
      std::cout << input_line[i] << "\n";
    }  //check if I have right vec
    */
    if (execve(input_line[0], &input_line[0], envi) == -1) {
      std::cout << "Command " << input_line[0] << " not found" << std::endl;
    }
    input_line.clear();
  }
  else {
    waitpid(childPid, &status, WUNTRACED | WCONTINUED);
    if (WIFEXITED(status)) {
      printf(" Program exited with status %d\n", WEXITSTATUS(status));
    }

    if (WIFSIGNALED(status)) {
      printf("Program was killed by signal %d\n", WTERMSIG(status));
    }
  }
}

void myShell::executeVal(std::string & input_line, size_t & findEqual) {
  if (input_line[findEqual - 1] == ' ' || input_line[findEqual + 1] == ' ') {
    std::cout << "can't input val like this" << std::endl;

    return;
  }

  std::string key = input_line.substr(0, findEqual);
  std::string value = input_line.substr(findEqual + 1, input_line.size() - 1);
  //  for(std::vector<char>::iterator iter=(char)key.begin()
  // if(isalnum(key[i]==0&&key[i]!='_')
  //  {
  //  return;}
  // }
  int key_len = key.length();
  int value_len = value.length();
  //  std::cout << "length of key: " << key_len << std::endl;
  if (key_len == 0 || value_len == 0) {
    return;
  }
  for (int i = 0; i < key_len; i++) {  //check every bit
    if (isalnum(key[i]) == 0 && (key[i]) != '_') {
      return;
    }
  }

  // std::cout << "length of value: " << value_len << std::endl;
  for (int i = 0; i < value_len; i++) {  //check every bit
    if (isalnum(value[i]) == 0 && (value[i]) != '_') {
      return;
    }
  }

  // std::cout << "key: " << key << std::endl;
  // std::cout << "value: " << value << std::endl;
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (key.compare(it->first.first) == 0) {
      std::pair<std::string, std::string> tempP =
          std::make_pair(key, value);  //if has this value, replace
      inputVal.erase(it);
      inputVal[tempP] = 0;
      return;
    }
  }
  std::pair<std::string, std::string> temp = std::make_pair(key, value);
  inputVal[temp] = 0;
  // std::cout << "map size: " << inputVal.size() << std::endl;
  // inputVal["abc"] = "fdadfa";  //first

  //testx
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    std::cout << it->first.first << "=" << it->second << std::endl;
  }
  return;
}

void myShell::outputValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                          std::string & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  /*std::string tempConvert;  //convert the rest of the vector into a string
  for (size_t i = 1; i < input.size(); i++) {
    tempConvert.append(input[i]);
  }
  std::cout << "the rest of the vec:" << tempConvert << std::endl;*/
  std::istringstream convert(input);
  std::string parseD;
  std::vector<std::string> parseDollar;

  while (std::getline(convert, parseD, '$')) {
    parseDollar.push_back(parseD);
  }
  /*  for (size_t i = 0; i < parseDollar.size(); i++) {
    std::cout << "the" << i << ": " << parseDollar[i] << std::endl;
  }  //check the parsedollar
  */
  // std::cout << "the size of parse: " << parseDollar.size() << std::endl;
  for (size_t i = 1; i < parseDollar.size(); i++) {
    for (it = inputVal.begin(); it != inputVal.end(); ++it) {
      // std::cout << "the first: " << parseDollar[i] << std::endl;
      // std::cout << "the second: " << it->first << std::endl;
      //std::cout << parseDollar[i].compare(it->first) << std::endl;
      if (parseDollar[i].compare(it->first.first) == 0) {
        // std::cout << "correct" << std::endl;

        std::cout << it->first.second;

        continue;
        //find the key
      }
      size_t positionSign = parseDollar[i].size();
      // std::cout << "last cha: " << parseDollar[i][positionSign - 1] << std::endl;
      if (parseDollar[i][positionSign - 1] == '-') {
        // std::cout << "sub: " << parseDollar[i].substr(0, positionSign - 1) << std::endl;
        // std::cout << "it: " << it->first << std::endl;
        // std::cout << parseDollar[i].substr(0, positionSign - 1).compare(it->first) << std::endl;
        if (parseDollar[i].substr(0, positionSign - 1).compare(it->first.first) == 0) {
          std::cout << it->second << "-";
          //find the key
          continue;
        }
      }
    }
  }
  //  if (findFg == 1) {
  //  std::cout << std::endl;
  // }
}
void myShell::parseValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                         std::vector<std::string> & input) {
  //std::map<std::string, std::string>::const_iterator it;
  for (size_t i = 1; i < input.size(); i++) {
    // for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    // std::cout << "the first: " << parseDollar[i] << std::endl;
    // std::cout << "the second: " << it->first << std::endl;
    //std::cout << parseDollar[i].compare(it->first) << std::endl;

    outputValue(inputVal, input[i]);
    std::cout << " ";
  }
  std::cout << std::endl;
}
void myShell::executeSet(std::string & left,
                         std::string & input_line,
                         std::map<std::pair<std::string, std::string>, bool> & inputVal) {
  std::string temp;
  size_t sizeOfInput = input_line.size();
  size_t findFirstSpace = input_line.find(' ', 0);
  temp = input_line.substr(findFirstSpace + 1, sizeOfInput);
  size_t findSecondSpace = temp.find(' ', 0);
  size_t tempSize = temp.size();
  temp = temp.substr(findSecondSpace + 1, tempSize);
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (left.compare(it->first.first) == 0) {
      std::pair<std::string, std::string> tempP =
          std::make_pair(left, temp);  //if has this value, replace
      inputVal.erase(it);
      inputVal[tempP] = 1;
      return;
    }
  }
  //if has a new value
  std::pair<std::string, std::string> tempP = std::make_pair(left, temp);
  inputVal[tempP] = 1;
  std::cout << "parseTemp[1]:" << left << std::endl;
  std::cout << "right: " << temp << std::endl;
  return;
}
void myShell::executeExport(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                            std::vector<std::string> & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (input[1].compare(it->first.first) == 0) {
      if (it->second == 0) {
        return;
      }
      std::string env = it->first.first + "=" + it->first.second;
      std::cout << "String pair: " << env << std::endl;
      putenv((char *)env.c_str());
      std::cout << "env: " << getenv(it->first.first.c_str()) << std::endl;
      return;
    }
  }
}
void myShell::excuteInc(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                        std::string & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (input.compare(it->first.first) == 0) {
      std::istringstream stream(it->first.second);
      int num;
      stream >> num;
      std::cout << "convert " << it->first.second << "to num: " << num << std::endl;
      num++;
      std::cout << "convert " << it->first.second << "to num: " << num << std::endl;
      std::string numConvert = std::to_string(num);
      //  stream >> numConvert;
      std::cout << "convert " << it->first.second << "to string: " << numConvert << std::endl;

      std::pair<std::string, std::string> tempP = std::make_pair(input, numConvert);
      bool store = it->second;
      inputVal.erase(it);
      inputVal[tempP] = store;
      return;
    }
  }
  std::string numConvert = "1";
  std::pair<std::string, std::string> tempP = std::make_pair(input, numConvert);
  inputVal[tempP] = 0;
  return;
}
