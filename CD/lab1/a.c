#include <stdio.h>
#include <stdlib.h> 
int main()
{
    FILE *fptr1, *fptr2;
    char filename[100], c;
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if(fptr1 == NULL)
    {
        printf("Cannot open file");
        exit(0);
    }
    c = fgetc(fptr1);
    int ch = 0, nl = 0;
    while (c != EOF)
    {
        if(c != '\n' && c != ' ') ch++;
        else if(c == '\n')nl++;
        c = fgetc(fptr1);
    }
    printf("%d %d\n",ch,nl+1);
    return 0;
}