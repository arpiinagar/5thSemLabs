#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int i = -1;
    unsigned int ui = 100;
    double d = 1.21212;
    float f = 182.2891;
    long l = 389283902;
    char ch = 'A';
    char s[] = "arpunagar";

    printf("\nInteger : %d", i);
    printf("\nUnsigned Integer : %u", ui);
    printf("\nFloat : %f", f);
    printf("\nDouble : %lf", d);
    printf("\nChar : %c", ch);
    printf("\nString : %s", s);
    // errno = EPERM;
    // printf("\nError NO. : %m\n");
}