#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    int socketd;
    socketd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un self_address;
    self_address.sun_family = AF_UNIX;

    strncpy(self_address.sun_path, "./socketfile", sizeof(self_address.sun_path)-1);

    int readVal = connect(socketd, (struct sockaddr*) &self_address, sizeof(self_address));

    if (readVal == -1) {
        printf("ERROR: Couldn't connect to server."); exit(1);
    }
    char buffer[150]; int index[5];
    while(1) {
        int n = read(0, buffer, sizeof(buffer));
        buffer[n] = '\0';
        write(socketd, buffer, strlen(buffer));
    }
    close(socketd);
    return 0;
}