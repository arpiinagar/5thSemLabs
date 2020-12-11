#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define pint pid_t
#include <sys/wait.h>

int main(){
	pint t;
	printf("Fork begins.\n");
	int t1 = 0;
	t = fork();
	if(t == -1){
		printf("ERROR\n");
		exit(0);
	}
	else if(t == 0){
		execl("./a", "a", NULL);
		exit(0);
	}
	else{
		wait(&t1);
		printf("Parent\n");
	}
	printf("End.\n");
}