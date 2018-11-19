#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>


int fibo(int n);
int main(int argc, char * argv[]){
	//if the amount of arguments is not 2, then don't proceed with program
	if(argc != 2){
		printf("Not enough arguments, type in output file and the amount of numbers to generate in sequence \n");
		exit(1);
	}
	int limit = atoi(argv[1]); //the amount of numbers to generate in sequence

	//if amount of numbers to generate is equal to or less than 0, then..		
	if(limit <=0){
		printf("Cannot perform Fibonacci on 0 or any negative numbers");		
	}

	const int SIZE =4096;
	const char* name ="Fibonacci";
	char* randomMessage = "Hello World";
	int shm_fd;
	void* ptr;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0,SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	for(int i=0; i<limit+1;i++){
		int fiboResult = fibo(i);
		sprintf(ptr,"%d", fiboResult);
		int flag=1;
		int temp = fiboResult;

		//updates pointer accordingly in order to avoid overwriting values
		while(flag==1){
			temp = temp/10;
			ptr++;
			if(temp==0){
				flag=0;				
			}
		}
		
		//if we are at the end of the for loop, don't print the comma
		if(i==limit-1){
			exit(1);
		}
		else{ //else, print the comma
			sprintf(ptr, "%s", ",");
			ptr++;
		}
	}

	return 0;
}

//Fibonacci algorithm
int fibo(int n){
	if(n==0 || n==1){
		return 1;
	}
	return fibo(n-1)+fibo(n-2);
}
