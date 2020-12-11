#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define pint pid_t
#include <sys/wait.h>

int main(){
	pint t;
	t = fork();
	int t1 = 0;
	if(t == -1){
		printf("Error.\n");
		exit(0);
	}
	else if(t == 0){
		int p1 = getpid();
		int p2 = getppid();
		printf("Child: %d \n Parent: %d\n",p1,p2);
		exit(0);
	}
	else{
		wait(&t1);
		int p1 = getpid();
		int p2 = getppid();
		printf("Child: %d \n Parent: %d\n",p1,p2);
		exit(0);
	}
	printf("Done.\n");
}