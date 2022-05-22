#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NOM_FICHIER "calcul.h"
#define FLAG IPC_CREAT | IPC_EXCL
#define MSG_FLAG 0

int msg_id;

void  raz_msg(int signal) {
	printf("\nSuppression de la file de message!\n");
	msgctl(msg_id, IPC_RMID, NULL);
	exit(0);
}


int main(int argc, char const *argv[])
{
	struct msg_struct msg;
	int i_sig;
	int result;
	key_t cle;
	msg_struct * message;
	//Creation du fichier

	/* liberer la zone de messages sur reception de n'importe quel signal */
	for (i_sig = 0 ; i_sig < NSIG ; i_sig++) {
		signal(i_sig, raz_msg);
	}
	if((cle = ftok(NOM_FICHIER, 10)) == -1){
		printf("erreur ftok\n");
		return EXIT_FAILURE;
	}
	if((msg_id = msgget(cle,IPC_CREAT|0666)) == -1){
		printf("erreur msg_id\n");
		return EXIT_FAILURE;
	}
	printf("SERVEUR: pret!\n");

	while (1 == 1) {
		/* reception */
		message = malloc(sizeof(msg_struct));

		if(msgrcv(msg_id, message, sizeof(msg_contenu), (long) 1, 0) == -1){
			printf("erreur msgrcv\n");
			return EXIT_FAILURE;
		}

		printf("SERVEUR: reception d'une requete de la part de: %d\n",(message->contenu).pid);
		/* preparation de la reponse */
		switch((message->contenu).operation){
			case '+':
				(message->contenu).operande1 = (message->contenu).operande1 + (message->contenu).operande2;
				break;
			case '-':
				(message->contenu).operande1 = (message->contenu).operande1 - (message->contenu).operande2;
				break;
			case '/':
				(message->contenu).operande1 = (message->contenu).operande1 / (message->contenu).operande2;
				break;
			case '*':
				(message->contenu).operande1 = (message->contenu).operande1 * (message->contenu).operande2;
				break;
			default:
				printf("erreur, mauvaise operation\n");

		}
		message->type = (message->contenu).pid;
		/* envoi de la reponse */

		msgsnd(msg_id, message, sizeof(msg_contenu), MSG_FLAG );
	}
	return EXIT_SUCCESS;
}
