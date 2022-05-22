#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
	printf("PID du pere : %d\n", getpid());
  for (int i  = 0; i < 10; i ++) {
    pid_t pid  = fork();
    if (pid == 0) {
      printf("je suis le fils numero %d et mon PID*2 est : %d \n",i,getpid()*2);
      exit(0);
    }
		printf("Je suis le pere (pid = %d)\n", getpid());
  }
  return 0;
}
