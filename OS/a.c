#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define pint pid_t
#include <sys/wait.h>

int main(){
	struct stat sb;
	int t;
	char filename[100];
	scanf("%s",filename);
	t = stat(filename,&sb);
	if(t){
		printf("ERROR.\n");
		return 1;
	}
	else{
		printf("ENODE number is: %lld\n", sb.st_ino);
		exit(0);
	}
	return 0;
}