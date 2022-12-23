#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

void stringGen(char *string, int len) {
    char validChars[] = {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int i = 0;
    while (len--) {
        int index = (double) rand() / RAND_MAX * (61);
        string[i++] = validChars[index];
    }
    string[i] = '\0';
}

int main() {
    // Random String Array Generator
    // Size argument = (input length + 1) because I'm adding '\0' at the end
    char src[251]; stringGen(src, 250);
    char string[50][7];
    for (int i = 0; i < 250; i++) {
        string[i/5][i%5] = src[i];
        if (i%5 == 4) {
            string[i/5][5] = '\n';
            string[i/5][6] = '\0';

        }
    }

    for (int i = 0; i < 50; i++) {
        printf("%s", string[i]);
    } 
    printf("These are the randomly generated strings.\n\n");

    // Shared Memory Implementation

	struct timespec start, stop;
	double accum;
	
	clock_gettime(CLOCK_REALTIME, &start);

    void *shared_memory;
    char buffer[100];
    int shmid;

    shmid = shmget((key_t) 1122, 1024, 0666|IPC_CREAT);
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n\n", shared_memory);

    // printf("Enter data\n");
    // read(0, buffer, 100);
    // strcpy(shared_memory, buffer);
    // printf("You wrote: %s\n", (char *) shared_memory);

    for (int i = 0; i < 10; i++) {
        printf("Sending next 5 strings.\n");
        for (int j = 5*i; j < 5*i+5; j++) {
            strcpy(shared_memory, string[j]);
            sleep(2);
        }
        printf("Last packet recieved: %s\n", (char *) shared_memory);
    }
    
    clock_gettime(CLOCK_REALTIME, &stop);
    
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/(double) BILLION;	
    printf("Time taken: %lfs\n", accum);
}
