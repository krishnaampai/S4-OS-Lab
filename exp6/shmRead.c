#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shm_id;
    key_t key = 12345;
    char *shm;

    // Get shared memory segment
    shm_id = shmget(key, SHM_SIZE,IPC_CREAT| 0666); 
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment
    shm = shmat(shm_id, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }
	printf("%s", shm);
	printf("Data read from shared memory\n"); 
    shmdt(shm);

    return 0;
}

