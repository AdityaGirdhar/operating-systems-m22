#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[100];
    int writePipe; int readPipe; 

    mkfifo("fifo1", 0777);
    mkfifo("fifo2", 0777);

    int ptr = 0; int i = 0;
    while (1) {
        while (i < ptr+5) {
            sleep(2);
            readPipe = open("fifo1", O_RDONLY);
            read(readPipe, buffer, sizeof(buffer));
            close(readPipe);

            printf("index %d: %s", i, buffer);
            i++;
        }

        ptr = i;
        writePipe = open("fifo2", O_WRONLY);
        sprintf(buffer, "%d", ptr-1);
        write(writePipe, buffer, sizeof(buffer));
        close(writePipe);

        if (ptr >= 50) break;
    }
}