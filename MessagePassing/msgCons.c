#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct buf{
	long mtype;
	char msgBuf[50];
}msg;


int main(){
	int qid = msgget(ftok(".",'Z'), IPC_EXCL | IPC_CREAT | 0666);
	
	msgrcv(qid, &msg, sizeof(msg), 111,0);

	printf("msg received : %s \n", msg.msgBuf);
	
	msgctl(qid, IPC_RMID, NULL);	
	return 0;
}

