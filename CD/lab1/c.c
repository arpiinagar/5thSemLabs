#include <stdio.h>
#include <stdlib.h>
FILE *fptr1, *fptr2, *fptr3;

int main()
{
    char filename[100], *c ,*s;
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if(fptr1 == NULL)
    {
        printf("Cannot open file");
        exit(0);
    }
    scanf("%s",filename);
    fptr2 = fopen(filename,"r");
    if(fptr2 == NULL){
        printf("Cannot open file\n");
        exit(0);
    }
    scanf("%s",filename);
    fptr3 = fopen(filename,"w+");
    int turn = 0;
    int k = 0;
    for(;;){
        if(!turn){
            size_t len = 0;
            ssize_t read = getline(&c, &len, fptr1);
            if(read == -1){
                break;
            }
            fputs(c, fptr3);
        }
        else{
            size_t len = 0;
            ssize_t read = getline(&s, &len, fptr2);
            if(read == -1){
                break;
            }
            fputs(s, fptr3);
        }
        turn^=1;
    }
    printf("Done.\n");
}