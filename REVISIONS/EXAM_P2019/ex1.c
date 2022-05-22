#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define TAILLE_MIN 5



int recherche(int Tab[],int longueur,int val){
	int nbOccurence = 0;
	if(longueur > TAILLE_MIN){
		int milieu = longueur/2;
		pid_t pid = fork();
		switch (pid) {
			case -1:
				printf("Problème fork\n");
				exit(0);
				break;
			case 0:
				for(int i =0; i< milieu; i++){
					printf("%d\n", i);
					if(Tab[i] == val){
						nbOccurence++;
						printf("Le processus fils a trouvé une occurence de %d à l'index %d\n", val, i);
					}
				}
				exit(nbOccurence);
				break;
			default :
				for(int i =milieu; i< longueur; i++){
					printf("%d\n", i);
					if(Tab[i] == val){
						nbOccurence++;
						printf("Le processus père a trouvé une occurence de %d à l'index %d\n", val, i);
					}
				}
				int resFils;
				waitpid(pid,&resFils,0);
				nbOccurence+=WEXITSTATUS(resFils);
		}
	}else{
		for(int i =0; i< longueur; i++){
			if(Tab[i] == val){
				nbOccurence++;
				printf("Le processus père a trouvé une occurence de %d à l'index %d\n", val, i);
			}
		}
	}
	return nbOccurence;
}

int main(int argc, char const *argv[]) {

	int Tab[] = {1,2,4,7,8,4,3,1,4};

	int val = 4;

	int retour = recherche(Tab, 9, val);
	printf("nbOccurence : %d\n",retour);

	return 0;
}
