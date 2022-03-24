#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void exo4_1(){
  sighandler_t code = signal(SIGINT,SIG_IGN);
  while(1);
  exit(0);
}

int main(int argc, char const *argv[]) {
  exo4_1();
}
