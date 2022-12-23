#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() {
    void *shared_memory;
    char buffer[100];
    int shmid;

    shmid = shmget((key_t) 1122, 1024, 0666);
    //printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    //printf("Process attached at %p\n", shared_memory);

    for (int i = 0; i < 10; i++) {
        for (int j = 5*i; j < 5*i+5; j++) {
            sleep(1);
            printf("index %d: %s", j, (char *) shared_memory);
            char id[2]; sprintf(id, "%d", j);
            strcpy(shared_memory, id);
            sleep(1);
        }
    }
}