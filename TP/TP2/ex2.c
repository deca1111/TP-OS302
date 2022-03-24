#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

pid_t fils_H;
pid_t fils_M;
pid_t fils_S;


int nb_seconde = 0;
int nb_minute = 0;
int nb_heure =0;


void seconde();
void minute();
void heure();

void handler(){
}

int main(int argc, char const *argv[]) {
  fils_M = fork();

  if(fils_M == 0){//fils minute
    fils_H = fork();

    if(fils_H == 0){//fils heure
      signal(SIGUSR2,handler);
      while (1) {
        pause();
        heure();
      }
    }else{
      signal(SIGUSR1,handler);
      while (1) {
        pause();
        minute();
      }
    }
  }else{//pere (seconde)
    signal(SIGALRM,handler);
    alarm(1);
    while (1) {
      pause();
      seconde();
    }
  }
  return 0;
}


void seconde(){
  nb_seconde++;
  if(nb_seconde == 5){
    nb_seconde = 0;
    kill(fils_M,SIGUSR1);
  }
  printf("sec = %d\n", nb_seconde);
  alarm(1);
}

void minute(){
  nb_minute++;
  if(nb_minute == 5){
    nb_minute = 0;
    kill(fils_H,SIGUSR2);

  }
  printf("minute = %d\n", nb_minute);
}

void heure(){
  nb_heure++;
  printf("heure = %d\n", nb_heure);
}
