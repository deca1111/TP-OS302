#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int var1 = 100 ;
int p[2] ;
char ch[7];
int main () {
	int var2 = 50 ;
	/* processus père, point 1 */
	printf("Adresse de varl dans 1e processus pere:%p\n", &var1) ;
	printf("Adresse de var2 dans Ie processus pere :%p\n", &var2) ;
	printf("1 : Valeur de varl eL var2 dans fe processus pere --> %d %d \n", var1, var2);
	if (pipe(p) == -1) {
		printf ("Erreur de creation de tube \n");
		exit(1) ;
	}
	switch (fork()) {
	case (pid_t) -1 :
		printf ( "Erreur de creation de processus\n");
		exit (2) ;
	case (pid_t) 0 : /* processus fils*/
		close(p[1]);
		/*point2*/
		read(p[0], ch, 7) ;
		printf ("Chaine recuperee dans le fils : %s \n", ch) ;
		printf("Adresse de varl dans le processus f11s :%p\n", &var1);
		printf("Adresse de var2 dans le processus fils :%p\n", &var2);
		printf("2 : Valeur de var1 eL var2 dans 1e processus fils --> %d %d \n",var1, var2) ;
		var2 =var2*2;
		printf("3 : Valeur de var1 eL var2 dans 1e processus fils --> %d %d \n",var1, var2) ;
		sleep(3);
		printf("6 : Valeur de var1 eL var2 dans 1e processus fils --> %d %d \n",var1, var2) ;
		exit (0) ;
	default : /* processus pere */
		close(p[0]);
		/*pointS3*/
		write(p[1], "Je suis le pere", 15);
		sleep(2);
		printf("4 : Valeur de var1 eL var2 dans 1e processus pere --> %d %d \n",var1, var2) ;
		var1 = var1 * 3 ; var2 = var2 * 3;
		printf("5 : Valeur de var1 eL var2 dans 1e processus pere --> %d %d \n",var1, var2) ;
		sleep(2);
		exit (0) ;
	}
}
