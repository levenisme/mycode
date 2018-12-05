#include "myShell.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
void myShell::executeCd(std::vector<char *> & cdArg) {
  if (cdArg.size() > 2) {
    std::cout << "size" << cdArg.size() << std::endl;
    perror("wrong cd arguments");
    return;
  }
  char * cdPath = cdArg[1];  //the input path
  chdir(cdPath);             //change work directory
}
//step2.2 if input has backslash

std::vector<std::string> myShell::checkParse(std::vector<std::string> & parse) {
  std::vector<std::string> checkParse;
  std::string temp;
  //check each element if it has a backslash
  for (size_t i = 0; i < parse.size(); i++) {
    int end = parse[i].size();
    if (parse[i][end - 1] == '\\') {
      temp = parse[i];
      temp.push_back(' ');
      temp.append(parse[++i]);  //if the input has only one/,consider it as a typo
      int tempEnd = temp.size();
      if (temp[tempEnd - 1] == '\\') {
        temp.push_back(' ');
        temp.append(parse[++i]);
        temp.erase(std::find(temp.begin(), temp.end(), '\\'));  //erase the typo
      }
      temp.erase(std::find(temp.begin(), temp.end(), '\\'));  //erase the typo

      checkParse.push_back(temp);
    }
    else {
      std::string temp2 = parse[i];
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
//parse the path first in parsePath, then find the right one and execute in executePath
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
  std::string path;
  size_t n = input_line.find(" ");
  std::string inputArg = input_line.substr(0, n);
  std::vector<std::string>::iterator it = parseP.begin();
  while (it != parseP.end()) {  //check every path if correct
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
          if (inputArg.compare(file_name) == 0) {  //if the command is found
            path = (*it) + "/" + input_line;       //expand the name
                                                   // std::cout << "path: " << path << std::endl;
            closedir(curr_dir);
            return path;
          }
        }
      }
      closedir(curr_dir);
    }
    ++it;
  }
  return input_line;  //cannot find path, the input may have right path
}
// find the path and execute
std::string myShell::searchPath(std::string input_line) {
  const char * pathSig = "PATH";
  path = getenv(pathSig);  //use the var
  std::vector<std::string> parseP = parsePath(path);
  std::string search;
  search = executePath(parseP, input_line);

  return search;
}
//execute commands
void myShell::execution(std::string & input, std::vector<char *> & input_line, char * env[]) {
  bool rediFg = 0;
  pid_t childPid = fork();
  int status;
  if (childPid == -1) {
    perror("cannot execute");
    exit(EXIT_FAILURE);
  }
  else if (childPid == 0) {
    std::vector<std::string> temp;  //if have >
    std::istringstream stringIn(input);
    std::string word;
    int i = 0;
    for (; input_line[i] != NULL; i++) {
      if (strcmp(">", input_line[i]) == 0) {
        rediFg = 1;
        break;
      }
    }

    if (rediFg) {
      std::cout << "check new filename: " << input_line[i + 1] << std::endl;
      int fd = open(
          input_line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      dup2(fd, 3);
      close(fd);
    }

    if (execve(input_line[0], &input_line[0], env) == -1) {
      std::cerr << "Command " << input << " not found" << std::endl;
      return;
    }
    input_line.clear();
  }

  waitpid(-1, &status, WUNTRACED | WCONTINUED);
  if (WIFEXITED(status)) {
    printf(" Program exited with status %d\n", WEXITSTATUS(status));
  }

  if (WIFSIGNALED(status)) {
    printf("Program was killed by signal %d\n", WTERMSIG(status));
  }
}

//execute the commands for values
void myShell::executeVal(std::string & input_line, size_t & findEqual) {
  if (input_line[findEqual - 1] == ' ' || input_line[findEqual + 1] == ' ') {
    std::cerr << "can't input val like this" << std::endl;
    return;
  }
  //address different cases
  std::string key = input_line.substr(0, findEqual);
  std::string value = input_line.substr(findEqual + 1, input_line.size() - 1);
  int key_len = key.length();
  int value_len = value.length();
  if (key_len == 0 || value_len == 0) {
    return;
  }
  for (int i = 0; i < key_len; i++) {  //check every bit
    if (isalnum(key[i]) == 0 && (key[i]) != '_') {
      return;
    }
  }
  for (int i = 0; i < value_len; i++) {  //check every bit
    if (isalnum(value[i]) == 0 && (value[i]) != '_') {
      return;
    }
  }

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
  /*
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    std::cout << it->first.first << "=" << it->second << std::endl;
    }*/
  return;
}
//print the value into the screen
void myShell::outputValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                          std::string & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  std::istringstream convert(input);
  std::string parseD;
  std::vector<std::string> parseDollar;

  while (std::getline(convert, parseD, '$')) {
    parseDollar.push_back(parseD);
  }
  for (size_t i = 1; i < parseDollar.size(); i++) {
    for (it = inputVal.begin(); it != inputVal.end(); ++it) {
      if (parseDollar[i].compare(it->first.first) == 0) {
        std::cout << it->first.second;
        continue;
      }
      size_t positionSign = parseDollar[i].size();
      if (parseDollar[i][positionSign - 1] == '-') {
        if (parseDollar[i].substr(0, positionSign - 1).compare(it->first.first) == 0) {
          std::cout << it->first.second << "-";
          continue;
        }
      }
    }
  }
}
//parse the value and then the value has right format
void myShell::parseValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                         std::vector<std::string> & input) {
  for (size_t i = 1; i < input.size(); i++) {
    outputValue(inputVal, input[i]);
    std::cout << " ";
  }
  std::cout << std::endl;
}
//execute set command
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
  inputVal[tempP] = 1;  //if the left value equals to 1, it means it can be export
  //  std::cout << "parseTemp[1]:" << left << std::endl;
  // std::cout << "right: " << temp << std::endl;
  return;
}
//execute export command
void myShell::executeExport(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                            std::vector<std::string> & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (input[1].compare(it->first.first) == 0) {  //find it the value exists
      if (it->second == 0) {                       //if it is not from set command, just return
        return;
      }
      std::string env = it->first.first + "=" + it->first.second;
      //      std::cout << "String pair: " << env << std::endl;
      //set the env into the environ
      setenv(it->first.first.c_str(), it->first.second.c_str(), 1);
      // std::cout << "env: " << getenv(it->first.first.c_str()) << std::endl;
      return;
    }
  }
}
//execute inc command
void myShell::excuteInc(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                        std::string & input) {
  std::map<std::pair<std::string, std::string>, bool>::const_iterator it;
  for (it = inputVal.begin(); it != inputVal.end(); ++it) {
    if (input.compare(it->first.first) == 0) {
      std::istringstream stream(it->first.second);
      int num;
      stream >> num;
      //      std::cout << "convert " << it->first.second << "to num: " << num << std::endl;
      num++;  //inc
      // std::cout << "convert " << it->first.second << "to num: " << num << std::endl;
      std::string numConvert = std::to_string(num);
      // std::cout << "convert " << it->first.second << "to string: " << numConvert << std::endl;
      //update the value
      std::pair<std::string, std::string> tempP = std::make_pair(input, numConvert);

      inputVal.erase(it);
      inputVal[tempP] = 1;  //it can be export
      return;
    }
  }
  //it does not exist
  std::string numConvert = "1";
  std::pair<std::string, std::string> tempP = std::make_pair(input, numConvert);
  inputVal[tempP] = 1;
  return;
}
