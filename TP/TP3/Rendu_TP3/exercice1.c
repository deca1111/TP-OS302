#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//define
int pipe_fd[2];


//definition des fonctions
void handler(){}


//definition du main
int main(int argc, char * argv[]){
  //si on a pas nos 2 arguments on return une erreur
  if(argc!=3){
    perror("Entrez 2 arguments");
    return EXIT_FAILURE;
  }else{
    //on créer un pipe
    pipe(pipe_fd);
    //on créer le premier fils
    pid_t fils = fork();
    switch (fils){
      //code du fils
      case 0:
        //on affecte la reception du signal SIGUSR1 a la fonction handler qui ne fait rien
        //cela est necessaire pour l'execution de la fonction pause
        signal(SIGUSR1,handler);
        //on attend de recevoir le signal du pere
        pause();
        //on redirige l'entree standard de la fonction system vers la sortie de notre tube
        dup2(pipe_fd[0],STDIN_FILENO);
        //on effectue la deuxieme fonction passee en argument du programme
        system(argv[2]);
        exit(0);
      //si on a une erreur au niveau du fork
      case -1:
        perror("Erreur dans la creation du fils");
        return EXIT_FAILURE;
      //code du pere
      default:
        //on redirige la sortie standard de la fonction system vers l'entree de notre tube
        dup2(pipe_fd[1],STDOUT_FILENO);
        //on effectue la premiere fonction passee en argument du programme
        system(argv[1]);
        //on envoie un signal au fils pour lui signaler qu'il peut faire sa fonction
        kill(fils, SIGUSR1);
        exit(0);
        break;
    }
  }
  return 0;
}
