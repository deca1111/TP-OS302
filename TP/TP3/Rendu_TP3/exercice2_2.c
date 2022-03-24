#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
//define
//nom absolue du fifo
#define NAME_FIFO "/tmp/fifo"

//definition du main
int main(int argc, char * argv[]){
  //creation des variables
  FILE * fichier_tube;
  //ouvrir le tube en ecriture
  //si il n'existe pas alors un fichier est cree
  fichier_tube = fopen(NAME_FIFO, "w");
  //si on a une erreur d'ouverture du tube on renvoie une erreur
  if(fichier_tube == NULL){
    printf("Erreur ouverture du fichier ecriture");
    return EXIT_FAILURE;
  }
  //si on pas le bon nombre de parametre on retourne une erreur
  if(argc != 2){
    printf("Rentrez un parametre\n");
    return EXIT_FAILURE;
  }
  //on ecrit l'argument d'entree dans le tube
  fputs(argv[1],fichier_tube);
  //on ferme le tube
  fclose(fichier_tube);
  //on reouvre le tube pour l'actualiser
  fichier_tube = fopen(NAME_FIFO, "w");
  //on efface tout ce qu'il y a dedans en ecrivant rien dedans
  fputs("",fichier_tube);
  //on ferme le fichier
  fclose(fichier_tube);
  return 0;
}
