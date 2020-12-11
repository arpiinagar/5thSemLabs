
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define pint pid_t
#include <sys/wait.h>

int main(){
	struct stat sb;
	char path[100], path1[100];
	scanf("%s",path);
	scanf("%s",path1);
	int t;
	t = symlink(path,path1);
	if(t){
		printf("ERROR\n");
		return 1;
	}
	printf("DONE\n");
	t = unlink(path1);
	if(t){
		printf("ERROR\n");
		return 1;
	}
	printf("DONE\n");
	return 0;
}