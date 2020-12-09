#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


void print(char* dir, int depth){
	DIR* dp;
	struct dirent *entry;
	struct stat statbuf;
	dp = opendir(dir);
	if(dp == NULL){
		printf("Cannot open Directory\n"); exit(0);
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL){
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0 ) continue;
			printf("\n Name: %s \t depth: %d\n",entry->d_name, depth);
			print(entry->d_name,depth+1);
		}
		else{
			printf("\n Name: %s \t depth: %d\n",entry->d_name, depth);
		}
	}
	chdir("..");
	closedir(dp);
}

int main(){
	print("..",0);
	return 0;
}