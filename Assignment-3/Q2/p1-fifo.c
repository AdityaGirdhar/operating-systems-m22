#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define BILLION 1000000000L

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

    // FIFO Implementation

    char buffer[10];

    mkfifo("fifo1", 0777);
    mkfifo("fifo2", 0777);
    int writePipe, readPipe;
	
	struct timespec start, stop;
	double accum;
	
	clock_gettime(CLOCK_REALTIME, &start);
	
    int ptr = 0;
    while (1) {
        printf("Sending next 5 strings\n");

        for (int i = ptr; i < ptr+5; i++) {
            writePipe = open("fifo1", O_WRONLY);
            write(writePipe, string[i], sizeof(string[i]) + 1);
            sleep(1);
            close(writePipe);
        }

        readPipe = open("fifo2", O_RDONLY);
        read(readPipe, buffer, sizeof(buffer));
        close(readPipe);

        printf("Last packet recieved: %d\n", atoi(buffer));
        ptr += 5; if (ptr >= 50) break;
    }
    
    clock_gettime(CLOCK_REALTIME, &stop);
    
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/(double) BILLION;	
    printf("Time taken: %lfs\n", accum);
}
