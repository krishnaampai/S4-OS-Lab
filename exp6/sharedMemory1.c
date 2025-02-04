#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
int main(){
	int shm_id;
	key_t key = 12345; // manually generate a key
	char *shm;
	
	//key = ftok("sgdh" , 'K'); // Generate key using file
	shm_id = shmget(key, SHM_SIZE,IPC_CREAT|0666);
	
	shm = shmat(shm_id , NULL, 0);
	sprintf(shm, "Hello, shared memory!\n");
	printf(shm);
	printf("Data written to shared memory\n"); 
	
	shmdt(shm);
	return 0;
}
