#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//define

pid_t pid_fils[3];


//definition des fonctions
void seconde();
void minute();
void heure();
void handler(){}
void fils(int num);


//definition du main
int main(int argc, char * argv[]){
  signal(SIGUSR1,handler);
  pid_t pid_fils;
  for(int i_fils = 0; i_fils < 3; i_fils ++){
    pid_fils = fork();
    switch (pid_fils){
      case 0:
      printf("Coucou");
        fils(i_fils);
        break;
      case -1:
        printf("Erreur creation %d fils\n",i_fils);
        return EXIT_FAILURE;
    }
  }
  alarm(1);
  return EXIT_SUCCESS;
}

//ecriture des fonctions
void fils(int num){
  pid_fils[num] = getpid();
  int seconde;
  int minute;
  int heure;
  switch (num){
    case 0:
    while(1){
      signal(SIGALRM,handler);
      pause();
      printf("Seconde : %d\n", seconde);
      if(seconde == 60){
        seconde = 0;
        kill(pid_fils[1],SIGUSR1);
      }else{
        seconde ++;
      }
    }
      break;
    case 1:
      while(1){
        pause();
        printf("minute : %d\n", minute);
        if(minute == 60){
          minute = 0;
          kill(pid_fils[2],SIGUSR1);
        }else{
          minute ++;
        }
      }
      break;
    case 2:
      while(1){
        pause();
        printf("minute : %d\n", minute);
        if(minute == 60){
          minute = 0;
          kill(pid_fils[2],SIGUSR1);
        }else{
          minute ++;
        }
      }
      break;
    default:
      perror("probleme");
      exit(0);
  }
  exit(pid_fils[num]);
}
