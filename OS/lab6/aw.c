#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <assert.h>
#include <string.h>
#define MAX 10 

struct msg_buf {
	int msg_t;
	char msg[100];
}msg1;

int main(){
	key_t key;
	int msgid;
	key = ftok("file",65);
	msgid = msgget(key,0666 | IPC_CREAT);

	printf("Write Data : "); 
    fgets(msg1.msg,MAX,stdin); 
    msgsnd(msgid, &msg1, sizeof(msg1), 0); 
    printf("Data send is : %s \n", msg1.msg);
    return 0; 
}