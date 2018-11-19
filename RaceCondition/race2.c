#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <stdlib.h>

int count;
int turn=0;

void *thread1(void *param){
	char i, tmp;
	srand(time(0));
	int randy = (intptr_t) param; //receiving the argument that contains the actual random number seed, and placing it inside a variable
	for(int i=0;i<3;i++){

		while(turn!=0);

		int number = rand()% randy;
		//ENTRY SECTION
		printf("1st Thread Entry#%d to critical section: count=%d\n", i+1, count);	
		//Begin with critical section		
		tmp = count;
		sleep(number);
		count = tmp+1;
		//End of critical section
		printf("1st Thread Exit#%d from critical section: count=%d\n", i+1, count);
		//exit section	
		turn =1;
	}	
	pthread_exit(0);
}


void *thread2(void *param){
	char i, tmp;
	srand(time(0));	
	int randy = (intptr_t) param; //receiving the argument that contains the actual random number seed, and placing it inside a variable

	for(int i=0;i<3;i++){

		while(turn!=1);
		int number = rand()% randy;
		//ENTRY SECTION
		printf("2nd Thread Entry#%d to critical section: count=%d\n",i+1, count);	
		//Begin with critical section		
		tmp = count;
		sleep(number);
		count = tmp-1;
		//End of critical section
		printf("2nd Thread Exit#%d from critical section: count=%d\n",i+1, count);
		//exit section	
		turn =0;
	}	
	pthread_exit(0);
}

int main(int argc, char *argv[]){
	//checks if the amount of arguments is valid or not	
	if(argc!=2){
		printf("Enter an integer argument alongside the .out file name, exiting program now");
		exit(0);	
	}
	int input = atoi(argv[1]);
	count=5;
	printf("Initial value of count = %d\n", count);
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//creating threads which will then execute concurrently
	pthread_create(&tid1, &attr, thread1, (void*)(intptr_t)input);
	pthread_create(&tid2, &attr, thread2, (void*)(intptr_t)input);
	//the execution of threads will then terminate
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("After threads complete,  count = %d\n", count);
	exit(0);
}

