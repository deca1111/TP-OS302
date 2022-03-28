#include "calcul.h"

#define NOM_FICHIER "calcul.h"
#define NOM_FICHIER2 "serveur.c"
#define FLAG 0

#define MSG_FLAG 0

int main(int argc, char *argv[]){
  int msg_id;
  key_t cle;


  if (argc != 2) {
    printf("Usage: %s \"texte en minuscule\"", argv[0]);
    printf("%d\n", argc);
    return EXIT_FAILURE;
  }
  cle = ftok(NOM_FICHIER, 10);
  msg_id = msgget(cle, FLAG);
  if(msg_id == 0){
    printf("erreur msg_id\n");
    return EXIT_FAILURE;
  }
  printf("CLIENT %d: preparation du message contenant le message suivant: [%s]\n", getpid(), argv[1]);

  msg_struct * message = malloc(sizeof(msg_struct));
  strcpy((message->contenu).message, argv[1]);
  (message->contenu).pid = getpid();
  message->type = 1;
  printf("CLIENT %d: envoi du message: [%s]\n",getpid(),(message->contenu).message);
  if( msgsnd(msg_id, message, sizeof(msg_contenu), MSG_FLAG ) == -1){
		printf("erreur msgsnd\n");
		return EXIT_FAILURE;
	}

  if(msgrcv(msg_id, message, sizeof(msg_contenu), (long) getpid(), 0) == -1){
		printf("erreur rcv\n");
		return EXIT_FAILURE;
	}
  printf("CLIENT: resultat recu depuis le serveur %d : [%s]\n",(message->contenu).pid, (message->contenu).message);

  return EXIT_SUCCESS;
}
