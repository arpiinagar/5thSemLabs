#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

int min(int a,int b){
    if(a < b) return a;
    else return b;
}

int main(int argc, char *argv[])
{
    int fd;
    char buf[100][100];
    char ch;
    int i, j;
    i = j = 0;
    if(argc != 2)
    {
        printf("Need 2 args\n");
        exit(0);
    }
    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        printf("Cant open this file\n");
        exit(0);
    }
    while(read(fd, &ch, 1) == 1)
    {
        if(ch != '\n')
        {
            buf[i][j] = ch;
            j++;
        }
        else
        {
            buf[i][j] = '\0';
            j = 0, i++;
        }
    }
    int k = i;
    for(int i = 0; i < min(20, k); i++)
    {
        printf("%s\n", buf[i]);
    }
    if(k > 20)
    {
        int i = 20;
        int p = i;
        while(i <= k)
        {
            char x;
            scanf("%c",&x);
            for(; i < min(p+20, k); i++)
            {
                printf("%s\n", buf[i]);
            }
            i+=20;
            p+=20;
        }
    }
}