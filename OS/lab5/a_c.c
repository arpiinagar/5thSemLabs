#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main()
{
    char *myfifo="myfifo";
    mkfifo(myfifo,0777);
    int i=0,fd;
    char str[80];
    while(i<4)
    {
        fd=open(myfifo,O_RDONLY);
        //printf("Enter the integer:\n");
        //scanf("%c",ch);
        read(fd, str, 80); 
        close(fd);
        printf("The number entered: %s\n", str); 
        i++;
    }
}