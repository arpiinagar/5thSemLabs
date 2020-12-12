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

void U();
void V();
void W();

void S()
{
    U();
    V();
    W();
}

void U()
{
    if(s[curr] == '(')
    {
        curr++;
        S();
        if(s[curr] != ')')
        {
            invalid();
        }
        curr++;
    }
    else if(s[curr] == 'a')
    {
        curr++;
        S();
        if(s[curr] != 'b')
        {
            invalid();
        }
        curr++;
    }
    else if(s[curr] == 'd'){
        curr++;
    }
    else{
        invalid();
    }

}

void V(){
    if(s[curr] == 'a'){
        curr++;
        V();
    }
}

void W(){
    if(s[curr] == 'c'){
        curr++;
        W();
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