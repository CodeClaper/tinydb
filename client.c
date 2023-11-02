#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pthread.h>
#include "input.h"

//Execute meta stament.
static bool meta_statment(char *input) {
    if (strcmp("clear", input) == 0 || strcmp("cls", input) == 0) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        return true;
    } else if (strcmp("history", input) == 0) {
        HIST_ENTRY** hist_entry = history_list();
        if (hist_entry == NULL) {
            fprintf(stdout, "Empty.\n");
            return true;
        }
        HIST_ENTRY *hist;
        for (uint32_t i = 0; (hist = *(hist_entry + i)) != NULL; i++ ) {
            fprintf(stdout, "%d\t%s\n", (i + 1), hist->line);
        }
        return true;
    }
    return false;
}

/**
 * Protocol symbol
 * META: message meta part
 * END: message end symbol
 *
 */
void db_receive(int server_fd) {
    while(1) {
        size_t len;
        if (recv(server_fd, &len, sizeof(len), 0) < 0)
            break;
        char *buff = malloc(len + 1);
        memset(buff, 0, len + 1);
        if (recv(server_fd, buff, len, 0) < 0)
            break;
        if (strcasecmp("Over", buff) == 0)
            break;
        printf("%s\n", buff);
    }
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
    while(1) {
        char *input = readline("tinydb > ");
        if (is_empty(input)) {
            break;
        }
        if (strcmp("exit", input) == 0) {
            printf("Goodbye.\n");
            break;
        }
        if(meta_statment(input)) {
            add_history(input);
            free(input);
            continue;
        }
        char *sql = malloc(1024);
        memset(sql, 0, 1024);
        strcpy(sql, input);
        size_t result = send(sock_fd, sql, 1024, 0);
        if (result == -1) {
            fprintf(stderr, "Send fail.");
            exit(1);
        }
        db_receive(sock_fd);
        add_history(sql);
        free(sql);
        free(input);
    }
    close(sock_fd);
    return 0;
}
