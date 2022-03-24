#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char *argv[])
{
	pid_t pid_fils;
	pid_t ret_wait;
	int	etat;
	/*
	* On peut executer ce programme en lui passant diverses
	* commandes en argument, par exemple, si l'executable est fexec :
	* fexec /usr/bin/ps
	*/
	if (argc != 2) {
		printf("Utilisation : %s executable !\n", argv[0]);
		return EXIT_FAILURE;
	}

	printf ("Je suis le processus %d je vais faire fork\n", getpid());
	pid_fils = fork();
	switch (pid_fils) {
	case 0:
		printf("Coucou ! je suis le fils %d\n", getpid());
		printf("%d : Code  remplace par %s\n", getpid(), argv[1]);
		execl(argv[1], argv[1], NULL);
		printf("%d : Erreur lors du exec \n", getpid());
		return EXIT_FAILURE;
	case -1:
		perror("Le fork n'a pas reussi");
		return EXIT_FAILURE;
	default:
		/* le pere attend la fin du fils */
		printf ("Pere numero %d attend\n", getpid());
		ret_wait = wait(&etat);
		printf ("Le fils etait : %d ", ret_wait);
		printf ("... son etat etait :%04x (hexa)\n", etat);
	}
	return EXIT_SUCCESS;
}
