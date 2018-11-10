#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
std::string string_from_vector(std::vector<std::string> & vec) {
  std::string ss = 0;
  for (std::vector<std::string>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
    // ss=accumulate(begin(vec),end(vec),ss);
    ss = ss + *itr;
  }
  return ss;
}
size_t makeHash(std::ifstream & f) {
  std::string readf;
  std::hash<std::string> hash_fn;
  std::vector<std::string> filecontent;
  while (std::getline(f, readf)) {
    filecontent.push_back(readf);
  }
  readf = string_from_vector(filecontent);
  size_t hash = hash_fn(readf);
  return hash;
}
void deleteFile(std::pair<size_t, std::string> & pair,
                std::unordered_map<size_t, std::string> & hashMap) {
  std::unordered_map<size_t, std::string>::iterator it = hashMap.find(pair.first);
  if (it == hashMap.end()) {
    hashMap.insert(pair);
  }
  else {
    std::cout << "#Removing " << pair.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << pair.second << std::endl;
  }
}
void dirCheck(const std::string & dir, std::unordered_map<size_t, std::string> & hashMap) {
  DIR * dp = opendir(dir.c_str());
  if (!dp) {
    fprintf(stderr, "open directory failure");
    closedir(dp);
    exit(EXIT_FAILURE);
  }
  struct dirent * filename;
  while ((filename = readdir(dp)) != NULL) {
    std::string file(filename->d_name);
    if (filename->d_type == DT_DIR) {
      std::string next_dir = dir + "/" + file;
      dirCheck(next_dir, hashMap);
    }
    else if (filename->d_type == DT_REG) {
      std::string currentfile = dir + "/" + file;
      std::ifstream input(file.c_str());
      if (input.good()) {
        size_t curr_hash;
        curr_hash = makeHash(input);
        std::pair<size_t, std::string> curr_pair(curr_hash, currentfile);
        deleteFile(curr_pair, hashMap);
      }
      else {
        std::cout << "invalid file" << std::endl;
      }
    }
    else {
      std::cout << "invalid file" << std::endl;
    }
    closedir(dp);
  }
}
int main(int argc, char ** argv) {
  if (argc < 2) {
    perror("invalid input");
    return EXIT_FAILURE;
  }
  else {
    std::unordered_map<size_t, std::string> hashMap;  //create a hash map
    std::cout << "#!/bin/bash" << std::endl;
    for (int i = 0; i < argc; i++) {
      const std::string dir = argv[i];
      dirCheck(dir, hashMap);  //check all files
    }
  }
  return EXIT_SUCCESS;
}
