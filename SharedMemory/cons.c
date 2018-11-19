#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>

int main(){

	const int SIZE = 4096;
	const char* name = "Fibonacci";
	int shm_fd;
	void *ptr;
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if(shm_fd == -1){
		printf("Shared memory failed\n");
		exit(-1);
	}
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(ptr == MAP_FAILED){
		printf("Map failed\n");
		exit(-1);
	}
	printf("%s", (char *)ptr);
	if(shm_unlink(name) == -1){
		printf("Error removing %s\n",name);
		exit(-1);
	}
	return 0;
}

