#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *in, *out;
    in = (FILE *)fopen(argv[1], "r");
    out = (FILE *)fopen(argv[2], "w");
    if(in == NULL)
    {
        printf("Can't open the in");
        exit(0);
    }
    if(out == NULL)
    {
        printf("Can't open the out");
        exit(0);
    }
    int c = fgetc(in);
    while(c != EOF)
    {
        fputc(c, out);
        c = fgetc(in);
    }
    fclose(in);
    fclose(out);
    return 0;
}