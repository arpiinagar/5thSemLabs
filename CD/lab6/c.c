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

void A(){
    if(s[curr] == 'b'){
        curr++;
    }
    else{
        A();
        if(s[curr] == 'b') curr++;
        else invalid();
    }
}

void B(){
    if(s[curr] == 'd'){
        curr++;
    }
    else invalid();
}

void S(){
    if(s[curr] == 'a'){
        curr++;
        A();
        if(s[curr] == 'c'){
            curr++;
        }
        else invalid();
        B();
        if(s[curr] == 'e') curr++;
        else invalid();
    }
    else{
        invalid();
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