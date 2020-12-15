// Writing a set of 4 integers. Producer

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
    char arr[80];
    while(i<4)
    {
        fd=open(myfifo,O_WRONLY);
        printf("Enter the integer:\n");
        fgets(arr, 80, stdin); 
        write(fd,arr,strlen(arr)+1);
        close(fd);
        i++;
    }
}
