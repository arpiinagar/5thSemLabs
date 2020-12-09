#include <stdio.h>
#include <stdlib.h>
FILE *fptr1, *fptr2;
void work(char ch){
    if(ch == EOF){
        return;
    }
    char x = fgetc(fptr1);
    work(x);
    putc(ch, fptr2);
}

int main()
{
    char filename[100], c;
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if(fptr1 == NULL)
    {
        printf("Cannot open file");
        exit(0);
    }
    scanf("%s",filename);
    fptr2 = fopen(filename,"w+");
    c = fgetc(fptr1);
    work(c);
    printf("Copied.\n");
    return 0;
}