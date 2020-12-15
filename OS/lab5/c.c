#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	int fd1; 
	
	char * myfifo = "/tmp/myfifo"; 
	
	
	mkfifo(myfifo, 0666); 
	char str1[80]; 
	while (1) 
	{ 
		fd1 = open(myfifo,O_RDONLY); 
		read(fd1, str1, 80); 	
		printf("Read: %s", str1); 
		close(fd1); 
	} 
	return 0; 
} 

// Write:


#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>  
int main() 
{ 
	int fd;
	char * myfifo = "/tmp/myfifo";  
	mkfifo(myfifo, 0666);  
	char arr2[80]; 
	while (1) 
	{ 
		fd = open(myfifo, O_WRONLY);  
		fgets(arr2, 80, stdin);  
		write(fd, arr2, strlen(arr2)+1); 
		close(fd);
	} 
	return 0; 
} 