#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    int row;
    int col;
    char *type;
} TOKEN;

void print(TOKEN t)
{
    printf("< %d, %d, %s >\n", t.row, t.col, t.type);
}

int main()
{
    FILE *input, *output;
    char filename[100];
    scanf("%s", filename);
    input = fopen(filename, "r");
    output = fopen("testp.c", "w+");
    if(input == NULL)
    {
        printf("No file found\n");
        exit(0);
    }
    // remove pre processors
    char ch;
    do
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
    }
    while (ch != EOF);
    //remove comments
    fclose(input);
    fclose(output);
    input = fopen("testp.c", "r");
    output = fopen("testc.c", "w+");
    char ca, cb;
    cb = ' ';
    ca = fgetc(input);
    while (ca != EOF)
    {
        if(ca == ' ')
        {
            fputc(ca, output);
            while(ca == ' ')ca = fgetc(input);
        }
        if (ca == '/')
        {
            cb = fgetc(input);
            if (cb == '/')
            {
                while(ca != '\n')ca = fgetc(input);
            }
            else if (cb == '*')
            {
                do
                {
                    while(ca != '*')ca = fgetc(input);
                    ca = fgetc(input);
                }
                while (ca != '/');
            }
            else
            {
                fputc(ca, output);
                fputc(cb, output);
            }
        }
        else fputc(ca, output);
        ca = fgetc(input);
    }
    fclose(input);
    fclose(output);
    input = fopen("testc.c", "r");
    printf("Done\n");
    return 0;
}