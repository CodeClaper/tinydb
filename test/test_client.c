#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>


void receive(int server_fd) {
    uint32_t len;
    recv(server_fd, &len, sizeof(len), 0);
    char *buff = malloc(len + 1);
    memset(buff, 0, len + 1);
    recv(server_fd, buff, len, 0);
    printf("%s\n", buff);
}

int main() {
    int sock_fd;
    pthread_t new_thread;
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        fprintf(stderr, "Create socket fail.");
        exit(1);
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = inet_addr("127.0.0.1");
    address->sin_port = htons(4080);
    if (connect(sock_fd, (struct sockaddr *)address, sizeof(*address)) == -1) {
        fprintf(stderr, "Connet server fail.");
        exit(1);
    }

    for(uint32_t i = 0; i < 1000; i++) {
        char *sql = malloc(1024);
        memset(sql, 0, 1024);
        sprintf(sql, "insert into test values(%d, 'lisi', %d, 'beijing')", (i + 1), (i + 10));
        size_t result = send(sock_fd, sql, 1024, 0);
        if (result == -1) {
            fprintf(stderr, "Send fail.");
            exit(1);
        }
        receive(sock_fd);
        free(sql);
    }
    getchar();
    close(sock_fd);
}
