#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main(){
	pid_t p = fork();
	
	if (p<0){
		perror ("fork failed");
		exit(1);
	}
	else if (p==0){
		printf ("Child process pid : %d\n",getpid());
	}
	else{
		printf("parent process pid : %d\n", getpid());
	}
	return 0;
}
