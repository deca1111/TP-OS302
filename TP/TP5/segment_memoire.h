/*********************************************************************
 * OS302 - shm - Exercice 1                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#ifndef SEGMENT_MEM_H
#define SEGMENT_MEM_H

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

/* Cree un segment de memoire
 * taille : la taille du segment memoire a creer
 * nom    : le nom du fichier associe
 * cle    : associe au nom pour la construction d'une cle identifiant
 *          le segment memoire (on utilisant la fonction ftok)
 * retourne : l'identificateur du segment, ou -1 en cas d'erreur */
int cree_segment(int taille, char* nom, int cle);

/* Afficher toutes les informations concernant un segment de memoire
 * shmid : l'identificateur du segment
 * retourn -1 en cas d'erreur */
int afficher_info_segment(int shmid);


/* Detruie un segment de m�moire
 * shmid : l'identificateur du segment
 * retourn -1 en cas d'erreur */
int detruire_segment(int shmid);

#endif
