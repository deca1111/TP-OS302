#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  for (int i  = 0; i < 1000; i ++) {
    pid_t pid  = fork();
    if (pid == 0) {
      printf("je suis le fils mon PID*2 est : %d \n",getpid()*2);
      exit(0);
    }
  }
  return 0;
}
