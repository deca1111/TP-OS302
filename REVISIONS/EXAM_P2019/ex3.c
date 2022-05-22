#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define NOM_FICHIER "$HOME/.serveur"

void interruptHandler(int sig, siginfo_t* info, void* v){//faire des choses lors de l'appui CTRL+C puis terminer
	printf("\nAPPUI de CTRL+C\n");
	exit(0);
}

//serveur
int main(int argc, char const *argv[]) {
	struct sigaction act;
	act.sa_sigaction = &interruptHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);

	key_t cle;
	if((cle=ftok(NOM_FICHIER,10))==-1){
		printf("erreur lors de la création de la clé\n");
		return EXIT_FAILURE;
	}


	while (1) {
		printf("Salut\n");
		sleep(1);
	}
	return 0;
}
