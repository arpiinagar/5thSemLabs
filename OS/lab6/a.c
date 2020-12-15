#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10 

struct msg_buf {
	int msg_t;
	char msg[100];
}msg1;

int r =-1;
void palin(char s[]){
	char x[strlen(s)];
	for (int i = strlen(s)-1; i >=0; --i)
	{
		x[strlen(x)-i-1]= s[i];
	}
	for (int i = 0; i < strlen(s); ++i)
	{
		if(x[i] != s[i]){
			printf("NO.\n");
			r = 0;
			return;
		}
	}
	printf("YES.\n");
	r = 1;
}

int main(){
	key_t key;
	int msgid;
	// printf("%s\n", );
	key = ftok("progfile",65);
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgrcv(msgid,&msg1,sizeof(msg1),1,0);
	palin(msg1.msg);
	msgctl(msgid,IPC_RMID,NULL);
	return 0;	
}