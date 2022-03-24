#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main(int argc, char const *argv[])
{
	int msg_id;
	struct msg_struct msg;

	if (argc != 4) {
		printf("Usage: %s operande1 {+|-|*|/} operande2\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* il faut eviter la division par zero */
	/* A COMPLETER */
	/* ATTENTION : la file de messages doit avoir ete creee par le serveur. Il
	 * faudrait tester la valeur de retour (msg_id) pour verifier que cette
	 * creation a bien eu lieu. */

	msg_id = msgget(/* A COMPLETER */);
	printf("CLIENT %d: preparation du message contenant l'operation suivante:\
		   	%d %c %d\n", getpid(), atoi(argv[1]), argv[2][0], atoi(argv[3]));

	/* On prepare un message de type 1 à envoyer au serveur avec les
	 * informations necessaires */
	/* A COMPLETER */
	/* envoi du message */

	msgsnd(/* A COMPLETER */);

	/* reception de la reponse */

	msgrcv(/* A COMPLETER */);
	printf("CLIENT: resultat recu depuis le serveur %d : %d\n",

	/* A COMPLETER */);
	return EXIT_SUCCESS;
}
