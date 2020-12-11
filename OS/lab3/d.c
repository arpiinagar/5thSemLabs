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
		printf("Error\n");
		exit(0);
	}
	else if(t == 0){
		printf("Child.\n");
		exit(0);
	}
	else{
		printf("In Parent.\n");
	}
	char *argv[3] = {"ps", "-l", NULL};
  	execv("/bin/ps", argv);
	printf("Done.\n");
}