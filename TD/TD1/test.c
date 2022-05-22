#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


void test(){
	int num, pid;
	pid = fork();
	if(pid == 0){       /*child*/
			num = 1;
	}else if(pid > 0){  /*parent*/
			num = 2;
	}
	exit(num);
}

int main(int argc, char*argv[]){
	int result = 0;
	result += test();
	printf("%d\n",result );
}
