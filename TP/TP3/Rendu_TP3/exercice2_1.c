#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <string.h>
//define
//taille max du buffer
#define MAX 100
//mode du fifo: rw-rw-rw-
#define MODE_FIFO 0666
//nom absolue du fifo
#define NAME_FIFO  "/tmp/fifo"

//definition du main
int main(int argc, char * argv[]){
	//creation des variables
	char buffer[MAX];
	char clear[MAX] = "";
	FILE * fichier_tube;
	int exit = 1;


  if(mkfifo(NAME_FIFO,MODE_FIFO) == -1){
		printf("tube deja existant\n");
		//si le fifo est deja cree, on le detruit
		unlink(NAME_FIFO);
		//et on en cree un nouveau
		mkfifo(NAME_FIFO,MODE_FIFO);
	}
  printf("Creation du tube\n");
	//on ouvre le tube en lecture
	fichier_tube = fopen(NAME_FIFO, "r");
	//tant qu'on ordonne pas la fin de la connection
	while(exit){
		//on copie le contenue du tube dans le buffer
		fgets(buffer, MAX, fichier_tube);
		//si le tube contient exit ou EXIT
		if(!strcmp(buffer, "exit") || !strcmp(buffer,"EXIT")){
			printf("fermeture du tube\n");
			//on ferme le tube et on sort
			unlink(NAME_FIFO);
			return 0;
		}
		//si le buffer contient quelque chose
		if(strcmp(buffer, clear)){
			//on affiche le contenue du buffer
			printf("%s\n",buffer);
			//on ferme le tube
			fclose(fichier_tube);
			//on reouvre le tube en lecture
			fichier_tube = fopen(NAME_FIFO, "r");
		}

	}
	//on unlink le tube
	unlink(NAME_FIFO);
	return 0;
}
