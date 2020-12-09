#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    int i = 0;
    int k = 0;
    char buf[100][100];
    char ch;
    if(argc != 3)
    {
        printf("error\n");
        exit(1);
    }
    fd = open(argv[2], O_RDONLY);
    if(fd == -1)
    {
        printf("Cant open the file\n");
        exit(1);
    }
    while((read(fd, &ch, 1)) == 1)
    {
        if(ch != '\n')
        {
            buf[k][i] = ch;
            i++;
        }
        else
        {
            buf[k][i] = '\0';
            if(strstr(buf[k], argv[1]) != NULL) printf("line:%d %s\n", k + 1, buf[k]);
            i = 0;
            k++;
        }
    }
}