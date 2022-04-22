/*********************************************************************
 * OS302 - shm - Exercice 2                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#include <string.h>
#include <unistd.h>
#include "segment_memoire.h"

int main() {
  
  int pid;      // le PID du processus
  char *mem;    // pointeur vers le segment memoire
  int shmid;    // l'identificateur du segment memoire
  char *nom = (char *) malloc(15*sizeof(char));
  nom = "exo2.c";

  // a completer : creation du segment de memoire partagee
  // ...

  // creation du processus fils
  pid = fork();
  if (pid == -1) {
    perror("impossible de creer un processu fils!");
    exit(-1);
  }
  else if (pid == 0) {
    sleep(2);
    // je suis le fils!
    // a completer : s'attacher au segment et affichage de son contenu
    // ...
  }
  else {
    // je suis le pere!
    // a completer : attachement et ecriture sur le segment de memoire partagee
    // a completer : attendre la fin du fils + detacher le segment et le detruire
    // ...
  }
          
  return 0 ;
}
