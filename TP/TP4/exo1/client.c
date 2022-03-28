#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NOM_FICHIER "calcul.h"
#define FLAG 0
#define MSG_FLAG 0


int main(int argc, char const *argv[])
{
	int msg_id;
	key_t cle;

	if (argc != 4) {
		printf("Usage: %s operande1 {+|-|*|/} operande2\n", argv[0]);
		printf("%d\n", argc);
		return EXIT_FAILURE;
	}

	/* il faut eviter la division par zero */
	if((argv[3] == 0)&&(argv[2] == "/")){
		printf("Division par zero, erreur");
		return EXIT_FAILURE;
	}
	/* ATTENTION : la file de messages doit avoir ete creee par le serveur. Il
	 * faudrait tester la valeur de retour (msg_id) pour verifier que cette
	 * creation a bien eu lieu. */
	cle = ftok(NOM_FICHIER, 10);
	msg_id = msgget(cle, FLAG);
	if(msg_id == 0){
		printf("erreur msg_id\n");
		return EXIT_FAILURE;
	}
	printf("CLIENT %d: preparation du message contenant l'operation suivante:\
		   	%d %c %d\n", getpid(), atoi(argv[1]), argv[2][0], atoi(argv[3]));

	/* On prepare un message de type 1 à envoyer au serveur avec les
	 * informations necessaires */
	 msg_struct * message = malloc(sizeof(msg_struct));
	 (message->contenu).operande1 = atoi(argv[1]);
	 (message->contenu).operande2 = atoi(argv[3]);
	 (message->contenu).operation = argv[2][0];
	 message->type = 1;
	 (message->contenu).pid = getpid();
	/* envoi du message */

	msgsnd(msg_id, message, sizeof(msg_contenu), MSG_FLAG );

	/* reception de la reponse */

	msgrcv(msg_id, message, sizeof(msg_contenu), (long) getpid(), 0);
	printf("CLIENT: resultat recu depuis le serveur %d : %d\n",(message->contenu).pid, (message->contenu).operande1);
	return EXIT_SUCCESS;
}
