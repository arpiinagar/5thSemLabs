#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char filename[100];
    scanf("%s", filename);
    FILE *input = fopen(filename, "r");
    scanf("%s", filename);
    FILE *output = fopen(filename, "w+");
    if(input == NULL)
    {
        printf("No file found\n");
        exit(0);
    }
    char ch = ' ';
    for(;;)
    {
        ch = getc(input);
        if (ch == '#')
        {
            while (ch != '\n')
            {
                ch = getc(input);
            }
        }
        putc(ch, output);
        if(ch == EOF) break;
    }
    return 0;
}