/*********************************************************************
 * OS302 - shm - Exercice 2                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "segment_memoire.h"

int main() {

  int pid;
  char *mem;
  int shmid;
  char *nom = "exo2.c";

  shmid = cree_segment(100*sizeof(char),nom,1);

	if(shmid == -1){
		printf("Probleme creation segment\n");
		return EXIT_FAILURE;
	}else{
		pid = fork();
		if (pid == -1) {
			perror("impossible de creer un processus fils!");
			exit(-1);
		}else if (pid == 0) {//Processus fils
			sleep(1);
			mem = shmat(shmid,0,0);
			printf("Fils : voici le message que j'ai trouvé :\t[%s]\n",mem);
			printf("Fils : meurt\n");
		}else {//Processus pere
			mem = shmat(shmid,0,0);
			strcpy(mem,"Voici le message envoyé par ton père.");
			printf("Père : message envoyé, attente de la mort du fils\n");
			wait(0);
			if(detruire_segment(shmid) == -1){
				printf("Probleme fermeture segment\n");
				return EXIT_FAILURE;
			}else{
				printf("Pere : meurt\n");
			}
		}
	}
  return 0 ;
}


//fonction utiles

int cree_segment(int taille, char* nom, int cle){
	key_t c = ftok(nom, cle);
	return shmget(c,taille * sizeof(int), IPC_CREAT | 0666 );
}

int afficher_info_segment(int shmid){
	struct shmid_ds * structShmid = malloc(sizeof(struct shmid_ds));
	int res = shmctl(shmid,IPC_STAT,structShmid);
	if(res == 0){
		printf("Informations du segment :\n");
		printf("Appartenance et permission :\n\tCle fournie : %d\n\tUID du proprietaire : %d\n\tGID du proprietaire : %d\n\tUID du createur : %d\n\tGID du createur : %d\n\tPermissions : %u\n\tNumero de sequence : %u\n",
			structShmid->shm_perm.__key,
			structShmid->shm_perm.uid,
			structShmid->shm_perm.gid,
			structShmid->shm_perm.cuid,
			structShmid->shm_perm.cgid,
			structShmid->shm_perm.mode,
			structShmid->shm_perm.__seq
		);
		free(structShmid);
		return 0;
	}
	printf("CKASE\n");
	free(structShmid);
	return -1;
}

int detruire_segment(int shmid){
	return shmctl(shmid,IPC_RMID, NULL);
}
