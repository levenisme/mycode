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
  //execute the input
  void execution(std::vector<char *> & input_line, char * envp[]);
  void executeVal(std::string & input_line, size_t & findEqual);
  void outputValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                   std::string & input);
  // public:
  myShell();
  // void free(std::vector<char *> & input);  //free the mem
  // std::string getInput() { return input_line; }
  // char * getPath() { return path; }
  //char *getDir(){return dirName;}
  //  charVec(size_t size,nullptr){}
  void parseValue(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                  std::vector<std::string> & input);
  void executeSet(std::string & left,
                  std::string & input_line,
                  std::map<std::pair<std::string, std::string>, bool> & inputVal);
  void executeExport(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                     std::vector<std::string> & input);
  void excuteInc(std::map<std::pair<std::string, std::string>, bool> & inputVal,
                 std::string & input);
};

#endif
