#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void pere();
void fils();
int numPere = -1;
int numFils = 0;
pid_t pid_pere;
pid_t pid_fils;

int main(int argc, char const *argv[]) {
  pid_pere = getpid();
  pid_fils = fork();
  switch (pid_fils) {
  case 0:
    signal(SIGUSR1,fils);
    //sleep(1);
    kill(pid_pere,SIGUSR1);
    while(numFils <=100){
      pause();
    }
    break;
  case -1 :
    perror("Le fork n'a pas reussi");
    return EXIT_FAILURE;
  default :
    signal(SIGUSR1,pere);
    while(numPere <=100){
      pause();
    }
  }


  return 0;
}

void pere(){
  numPere+=2;
  if(numPere <= 100){
    printf("Pere : %d\n",numPere);
  }
  kill(pid_fils,SIGUSR1);
}


void fils(){
  numFils+=2;
  if(numFils <= 100){
    printf("Fils : %d\n",numFils);
  }
  kill(pid_pere,SIGUSR1);
}
