/*********************************************************************
 * OS302 - shm - Exercice 1                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#include "segment_memoire.h"

int main() {
  int shmid ;
  char *nom = (char *) malloc(100*sizeof(char)) ;
  nom = "exo1.c" ;
  shmid = cree_segment(100,nom,1) ;
  afficher_info_segment(shmid) ;
  detruire_segment(shmid) ;
  return 0 ;
}

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
