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
  
    int qid = msgget(ftok(".", 'Z'), 0);
    //if the message queue cannot be accessed, then exit program
    if(qid==-1){
	printf("Message queue cannot be accessed\n");
	exit(1);
    }
	
    message.mtype = 100;
 
    printf("Message queue access is a success\n"); 
    printf("Ready to enter characters through queue\n");
    printf("Enter a character followed by the enter key\n");
    printf("Enter 'Q' or 'q' to exit\n");
	
    int flag=1;
    while(flag!=0){
	int active=1;
	char input[50];
	//validation loop that determines if more than one character in a line has been entered,
	// keeps looping if more than one character has been entered, exits loop if one character has been entered
	do{
		scanf("%s",input);
		if(strlen(input)>1){
			printf("Invalid, more than one character in a single line has been entered\n");
		}
		else{
			active=0;
		}
	
	}while(active);
	
	//assigning recent input to the message's data in order to send message to queue
	sprintf(message.msgBuffer, "%s", input);
	msgsnd(qid, &message, sizeof(message), 0);
	
	//if user input is either Q or q, then exit both programs
	if(strcmp(input, "q")==0 || strcmp(input,"Q")==0){
		printf("Now exiting\n");
		flag=0;
	}
     }
    
    return 0;
}
