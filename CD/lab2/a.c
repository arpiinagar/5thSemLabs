#include <stdio.h>
#include <stdlib.h>
// HEY
int main()
{
    FILE *fptr1, *fptr2;
    char filename[100];
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if(fptr1 == NULL)
    {
        printf("Cannot open this file.\n");
        exit(	0);
    }
    scanf("%s", filename);
    fptr2 = fopen(filename, "w+");
    char ch;
    ch = fgetc(fptr1);
    const char space = ' ';
    char chdp = 'a';
    while(ch != EOF)
    {
    	ch = fgetc(fptr1);
    	if(ch == ' ' || ch == '\t'){
    		chdp = ' ';
        	continue;	
        }
    	
        if(chdp == ' ')putc(space, fptr2);
        putc(ch, fptr2);
        chdp = ch;
    }
    printf("Done.\n");
    return 0;
}