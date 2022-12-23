#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
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
    
    // UNIX Socket Implementation
    
    struct timespec start, stop;
	double accum;
	
	clock_gettime(CLOCK_REALTIME, &start);
    
    int server_socket;
    int client_socket;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    unlink("./socketfile");
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, "./socketfile", sizeof(server_address.sun_path)-1);
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    while (1) {
        printf("Waiting for client connection...\n");
        int client_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_length);
        printf("\n====== CLIENT CONNECTION ESTABLISHED ======\n");

        int read_val;
        int ptr = 0;
        char retBuffer[150];
        write(client_socket, retBuffer, strlen(retBuffer));
        while (read_val = read(client_socket, retBuffer, sizeof(retBuffer))) {
            printf("Sent first five strings.\n");
            for (int i = 0; i < 50; i++) {
                write(client_socket, string[i], strlen(string[i]));
                if (!(i%5) && i != 0) {
                    printf("Last packet recieved: %d\nSending next five strings.\n", i-1);
                }
                sleep(1);
            }
            printf("All strings sent!\n");
            break;
        }
        close(client_socket);
        printf("\n====== CLIENT CONNECTION TERMINATED ======\n");
        break;
    }
    
    clock_gettime(CLOCK_REALTIME, &stop);
    
	accum = (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec)/(double) BILLION;	
    printf("Time taken: %lfs\n", accum);
    
    return 0;
}
