#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <assert.h>
#include <string.h>
#define MAX 10 

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 

void isPalindrome(char str[]) 
{ 
    int l = 0; 
    int h = strlen(str) - 2;
    while (h > l) 
    {
        if (str[l++] != str[h--]) 
        { 
            printf("String: %s Verdict:Not Palindrome\n", str); 
            return; 
        } 
    } 
    printf("String:%s Verdict:Palindrome\n", str); 
} 
  
int main() 
{ 
    key_t key; 
    int msgid; 
    key = ftok("progfile", 65); 
    msgid = msgget(key, 0666 | IPC_CREAT); 
    msgrcv(msgid, &message, sizeof(message), 1, 0); 
    isPalindrome(message.mesg_text);
    msgctl(msgid, IPC_RMID, NULL); 
    return 0; 
} 
