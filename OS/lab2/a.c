#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


void print(char* dir){
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
			printf("\n%s\t%c",entry->d_name,);
		}
		else{
			printf("\n%s\t%c",entry->d_name);
		}
	}
	chdir(".");
	closedir(dp);
}

int main(){
	print("..");
	return 0;
}