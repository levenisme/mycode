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
void execution(std::vector<char *> & input_line);
void executeCd(std::vector<char *> & cdArg) {
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

std::vector<std::string> checkParse(std::vector<std::string> & parse) {
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
  return checkParse;
}
//step2.1
//parse the path first, then find the right one and execute
std::vector<std::string> parsePath(char * path) {
  std::istringstream temp(path);
  std::string pathtemp;
  std::vector<std::string> parse;
  while (std::getline(temp, pathtemp, ':')) {
    parse.push_back(pathtemp);
  }
  return parse;
}
std::string executePath(std::vector<std::string> parseP, std::string input_line) {
  DIR * curr_dir;
  struct dirent * ent;
  std::string path;
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
  return input_line;  //cannot find path
}
//colon-delimited parse
std::string searchPath(std::string input_line) {
  const char * pathSig = "PATH";
  char * path = NULL;
  path = getenv(pathSig);
  std::vector<std::string> parseP = parsePath(path);
  /* for (size_t i = 0; i < parseP.size(); i++) {
    std::cout << parseP[i] << "\n";
    }*/
  std::string search;
  search = executePath(parseP, input_line);
  return search;
}

void execution(std::vector<char *> & input_line) {
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
int main(void) {
  while (1) {
    char * path = get_current_dir_name();
    std::cout << "myShell:" << path << " $";
    free(path);
    std::string input_line;
    getline(std::cin, input_line);
    input_line = searchPath(input_line);  //verify if need to add path
    if (std::cin.eof()) {
      exit(EXIT_SUCCESS);
    }
    if (input_line == "exit") {
      exit(EXIT_SUCCESS);
    }

    std::string getCd = getenv("HOME");
    //  std::cout << "cdpath" << getCd << std::endl;

    std::vector<std::string> parseTemp;

    std::istringstream stringIn(input_line);
    std::string word;
    size_t findSlash = input_line.find('\\', 0);
    //  std::cout << "findslash" << findSlash << std::endl;
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
    parseTemp = checkParse(parseTemp);

    std::vector<char *> charVec(parseTemp.size(), nullptr);
    for (size_t i = 0; i < parseTemp.size(); i++) {  //convert string into char*
      charVec[i] = (char *)parseTemp[i].c_str();
    }

    // charVec.push_back(NULL);
    //check if press enter
    if (charVec.size() == 0) {
      continue;
    }
    if (strcmp(charVec[0], "cd") == 0) {
      executeCd(charVec);  //execute cd
    }
    else {
      charVec.push_back(NULL);
      execution(charVec);  //execute normal commands
    }
  }

  return EXIT_SUCCESS;
}
