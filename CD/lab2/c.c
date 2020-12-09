#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char keyword[32][32];
void getkey(){
    FILE *input = fopen("keyword.txt", "r");
    for (int i = 0; i < 32; ++i)
    {
        int j = 0;
        char ch = fgetc(input);
        while(ch != '\n'){
            keyword[i][j++] = ch;
            ch = fgetc(input); 
        }
         keyword[i][j] = '\0';
    }
}

void print(char* s){
    for (int i = 0; i < sizeof(s)/sizeof(char); ++i)
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        printf("%c",(char)(s[i]-32));
    }
    printf("\n");
}

int main ()
{
    char filename[100];
    scanf("%s", filename);
    FILE *input = fopen(filename, "r");
    getkey();
    char buf[100];
    int i = 0;
    char ch = fgetc(input);
    while(ch != EOF){
        if(ch == ' '){
            if(i!=0){
                for (int j = 0; j < 32; ++j)
                {
                    if(strcmp(keyword[j],buf) == 0){
                        print(buf);
                    }
                }
            }
            memset(buf,0,sizeof(buf));
            i = 0;
        }
        else{
            buf[i++] = ch;
        }
        ch = fgetc(input);
    }
    return 0;
}