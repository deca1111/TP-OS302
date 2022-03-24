#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>


void raz_msg(int signal) {
	printf("Suppression de la file de message!\n");
	msgctl(/* A COMPLETER */);
}

int msg_id;

int main(int argc, char const *argv[])
{
	struct msg_struct msg;
	int i_sig;
	int result;

	/* liberer la zone de messages sur reception de n'importe quel signal */

	for (i_sig = 0 ; i_sig < NSIG ; i_sig++) {
	/* A COMPLETER */
	}

	msg_id = msgget(/* A COMPLETER */);
	printf("SERVEUR: pret!\n");
	while (1 == 1) {
		/* reception */
		msgrcv(/* A COMPLETER */);
		printf("SERVEUR: reception d'une requete de la part de: %d\n",
		/* A COMPLETER */);
		/* preparation de la reponse */
		/* A COMPLETER */
		/* envoi de la reponse */
		msgsnd(/* A COMPLETER */);
	}
	return EXIT_SUCCESS;
}

