#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

//

int main(){
	pid_t pid1 = fork();

	if (pid1 >0){
		printf("je suis le pere %d \n",getpid());

		pid_t pid2 = fork();

		if (pid2 == 0) {
			printf("je suis le fils n°2 mon PID est : %d \n",getpid());
			sleep(2);
		}else if (pid1 >0){
			pid_t temp1 = wait(NULL);
			printf("mon fils n°%d est mort\n",temp1);

			pid_t temp2 = wait(NULL);
			printf("mon fils n°%d est mort\n",temp2);
		}else{
			printf("ERREUR dans fork\n");
		}
	}else if(pid1 == 0){
		printf("je suis le fils n°1 mon PID est : %d \n",getpid());
		sleep(3);
	}else{
		printf("ERREUR dans fork\n");
	}
	return 0;
}
