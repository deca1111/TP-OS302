#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define TAILLEMAX_EXE 30

typedef struct msg_contenu{
  char nom[TAILLEMAX_EXE];
  pid_t pid;
} msg_contenu;

typedef struct msg_struct {
    long type;
    msg_contenu contenu;
} msg_struct;


//#define NOM_FICHIER "$HOME/.serveur"
#define NOM_FICHIER "ex3.c"

int nbSigUsr = 0;
int nbMsgRecu = 0;
int msg_id = 0;

void interruptHandler(int sig, siginfo_t* info, void* v){//afficher des choses lors de l'appui CTRL+C puis terminer
	printf("\nNombre de message(s) recu : %d\nNombre de signal SIGUSR1 recu : %d\n",nbMsgRecu,nbSigUsr);
	msgctl(msg_id, IPC_RMID, NULL);//suppression file de message
	exit(0);
}

void sigusrHandler(int sig, siginfo_t* info, void* v){//compte le nombre de SIGUSR1 recu
	nbSigUsr++;
}

//serveur
int main(int argc, char const *argv[]) {
	//define variables
	msg_struct* message;

	//mise en place du handler sur SIGINT
	struct sigaction actInterrupt;
	actInterrupt.sa_sigaction = &interruptHandler;
	actInterrupt.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &actInterrupt, NULL);

	//mise en place du handler sur SIGUSR1
	struct sigaction actSigusr;
	actSigusr.sa_sigaction = &sigusrHandler;
	actSigusr.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &actSigusr, NULL);

	key_t cle;
	if((cle=ftok(NOM_FICHIER,10))==-1){//creation de la cle
		printf("erreur lors de la création de la clé\n");
		return EXIT_FAILURE;
	}


	if((msg_id = msgget(cle,IPC_CREAT|0666)) == -1){//creation de la file
		printf("erreur msg_id\n");
		return EXIT_FAILURE;
	}

	printf("SERVEUR: pret!\n");

	while (1) {
		message = malloc(sizeof(msg_struct));

		if(msgrcv(msg_id, message, sizeof(msg_contenu), (long) 1, 0) == -1){
			printf("erreur msgrcv\n");
			return EXIT_FAILURE;
		}
		nbMsgRecu ++;;
		printf("SERVEUR: reception d'une requete de la part de: %d\n",(message->contenu).pid);

		//preparation de la reponse
		message->type = (message->contenu).pid;
		(message->contenu).pid = getpid();
		strncpy((message->contenu).nom, "Bonjour !", TAILLEMAX_EXE);//recopie avec taille max.

		//envoi de la reponse
		msgsnd(msg_id, message, sizeof(msg_contenu), IPC_CREAT | IPC_EXCL );

	}
	return 0;
}
