#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int curr = 0;

char s[100];

void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void S();

void L();

void Ldash();

void S(){
    if(s[curr] == '('){
        curr++;
        L();
        if(s[curr] == ')'){
            curr++;
        }
        else invalid();
    }
    else if(s[curr] == 'a'){
        curr++;
    }
    else invalid();
}

void L(){
    S();
    Ldash();
}

void Ldash(){
    if(s[curr] == ','){
        curr++;
        S();
        Ldash();
    }
}


int main()
{
    printf("Enter the String:\n");
    scanf("%s", s);
    S();
    if(s[curr] == '$')
    {
        valid();
    }
    else
    {
        invalid();
    }
}