#ifndef __MYSHELL_H__
#define __MYSHELL_H__

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
class myShell
{
 public:
  std::string input_line;                                        //get input from stdin
  char * path;                                                   //get current path
  char * dirName;                                                //get dir, use for the output
  std::map<std::pair<std::string, std::string>, bool> inputVal;  //store the value in key
  std::vector<char *> charVec;                                   //parse the input
  void executeCd(std::vector<char *> & cdArg);                   //if I have cd command
  //check if input has backslash
  std::vector<std::string> checkParse(std::vector<std::string> & parse);
  //parse the path first, then find the right one and execute, only use if don't have input path
  std::vector<std::string> parsePath(char * path);
  //find the right path if have, if the input has path, return the former path
  std::string executePath(std::vector<std::string> parseP, std::string input_line);
  //get the path and search
  std::string searchPath(std::string input_line);
  //execute normal commands
  void execution(std::string & input, std::vector<char *> & input_line, char * envp[]);
  //execute input with value
  void executeVal(std::string & input_line, size_t & findEqual);
  //print the required value to the shell
  void outputValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                   std::string & input);
  //get the right input format if have value
  void parseValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                  std::vector<std::string> & input);
  //execute set command
  void executeSet(std::string & left,
                  std::string & input_line,
                  std::map<std::pair<std::string, std::string>, bool> & inputVal);
  //execute the export command
  void executeExport(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                     std::vector<std::string> & input);
  //execute the inc command
  void excuteInc(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                 std::string & input);
};

#endif
