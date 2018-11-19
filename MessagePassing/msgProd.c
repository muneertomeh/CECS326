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
	printf("crap\n");
	int qid = msgget(ftok(".",'Z'), IPC_EXCL | IPC_CREAT | 0666);
	msg.mtype=111;
	printf("write data");
	scanf("%s",msg.msgBuf);

	msgsnd(qid, &msg, sizeof(msg), 0);
	
	printf("reply received: %s\n", msg.msgBuf);

	return 0;
}
 
