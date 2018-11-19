#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int status;
	if(argc !=2){
		printf("Incorrect amount of arguments utilized, enter executable file and an integer argument");
		exit(1);	
	}
	pid_t pid;
	pid = fork(); //fork a child process that will execute the fibonacci producer program
	
	if(pid==-1){
		printf("Error fork has failed, exiting program\n");
		exit(1);
	}

	else if(pid ==0){ //currently in child process which will execute producer program
		printf("This is the first forked child process executing the producer program\n");	
		execv("sh_p.out", argv);
		exit(1);
	}

	else if(pid!=0){ //currently in parent process
		if(wait(&status)==-1){
			printf("Error, exiting program\n");
			exit(1);
		}
		pid = fork(); //fork another child process that will execute the fibonacci consumer program

		if(pid==-1){
			printf("Error fork has failed, exiting program\n");
			exit(1);
		}
		
		else if(pid==0){ //we are now in second child process that will execute the consumer program
			printf("This is the second forked child, executing the consumer program to view data\n");	
			execv("sh_c.out", argv);
			exit(1);
		}
		
		if(wait(&status)==-1){
			printf("Error, exiting program\n");
			exit(1);
		}
		exit(0);	
	}
	
	return 0;
}


