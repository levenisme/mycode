#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
int main(void) {
  /*
      第一个参数是程序的名字，第二个参数是被调用程序的参数，最后一个参数必须是NULL
      这个跟main函数的参数args数组很相似
     */
  char * pPath;
  pPath = getenv("PATH");
  char path[200];
  getcwd(path, sizeof(path));

  std::cout << "path" << pPath << std::endl << path << std::endl;
  char * argv[] = {(char *)"/bin/ls", (char *)"-1", NULL};
  execve(argv[0], argv, NULL);
  /*
     execve函数是替换原来的程序代码，但是进程PID不会变，文件描述符不会变，只是程序代码被替换了
     所以execve函数后面的语句都不会被执行
     */
  printf("program is end!\n");
  return 0;
}
