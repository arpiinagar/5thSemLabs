#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int curr = 0;

char str[100];

void S();

void T();

void Tprime();

void reject()

{

    printf("reject\n");

    exit(0);

}

void valid()

{

    printf("accept\n");

    exit(0);

}

void S()

{

    if(str[curr] == 'a')

    {

        curr++;

        return;

    }

    else if(str[curr] == '>')

    {

        curr++;

        return;

    }

    else if(str[curr] == '(')

    {

        curr++;

        T();

        if(str[curr] == ')')

        {

            curr++;

            return;

        }

        else

            reject();

    }

    else

        reject();

}

void T()

{

    S();

    Tprime();

}

void Tprime()

{

    if(str[curr] == ',')

    {

        curr++;

        S();

        return;

    }

}

int main()

{

    printf("Enter the String:\n");

    scanf("%s", str);

    S();

    if(str[curr] == '$')
    {

        valid();

    }

    else

        reject();

}