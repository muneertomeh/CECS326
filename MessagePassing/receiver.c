#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
 
// structure for message queue
struct buf {
    long mtype;
    char msgBuffer[50];
} message;
 
int main(){
    int qid = msgget(ftok(".", 'Z'), 0666 | IPC_CREAT);
    //if the creation of a message queue fails, then exit program
    if(qid==-1){
	printf("Message queue creation has failed\n");
    	exit(1);
    }
    printf("Message queue creation is a success\n");
    printf("Waiting on something to receive message, message type has to be of 100\n");
    
    int flag=1;
    while(flag==1){
   	msgrcv(qid, &message, sizeof(message), 100, 0);
   	printf("Got a character %c\n", message.msgBuffer[0]);
   	if(message.msgBuffer[0]=='q' || message.msgBuffer[0] == 'Q'){
    		flag=0;
   	}
    }

    
    //destroy the message queue
    msgctl(qid, IPC_RMID, NULL);
    printf("Message queue has been removed\n");
    return 0;
}
