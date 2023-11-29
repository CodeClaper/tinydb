#include <netinet/in.h>
#include <stdatomic.h>
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
#include "utils.h"

#define MAX_BUFF_SIZE 1<<20
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT 4080
#define BUFF_SIZE 1024

/* Execute meta stament. */
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

bool send_get(int fd) {
    char buff[3];
    /* Send message 'GET'*/
    sprintf(buff, "%s", "GET");
    return send(fd, buff, 3, 0) > 0;
}

/**
 * Protocol symbol
 * GET: get the server message
 * OVER: end of session.
 *
 */
void db_receive(int server_fd) {
    while(1) {
        ssize_t r;
        char buff[BUFF_SIZE];
        if ((r = recv(server_fd, buff, BUFF_SIZE, 0)) > 0) {
            if (strcmp(buff, "OVER") == 0) 
                break;
            else
                printf("%s", buff);
        }
        else
            break;
    }
}

/* Genrate address. */
static struct sockaddr_in *gen_address(int argc, char *argv[]) {
    int opt;
    char *optString = "h:p:";
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = PF_INET;
    while((opt = getopt(argc, argv, optString)) != -1) {
        switch(opt) {
            case 'h': {
                if (optarg)
                    address->sin_addr.s_addr = inet_addr(optarg);
                else 
                    address->sin_addr.s_addr = inet_addr(DEFAULT_HOST);
                break;
            }
            case 'p': {
                if (optarg)
                    address->sin_port = htons(atoi(optarg));
                else 
                    address->sin_port = htons(DEFAULT_PORT);
                break;
            }
            default: 
                fprintf(stderr, "Unrecognised parameter\n");
                exit(1);
                
        }
    }
    return address;
}

/* main
 * Command line parameters:
 * -h host
 * -p port
 * */
int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Bad command line arguement.");
        exit(1);
    }
    int sock_fd;
    pthread_t new_thread;
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        fprintf(stderr, "Create socket fail.");
        exit(1);
    }
    struct sockaddr_in *address = gen_address(argc, argv);
    if (connect(sock_fd, (struct sockaddr *)address, sizeof(*address)) == -1) {
        fprintf(stderr, "Connet server fail.");
        exit(1);
    }
    while(1) {
        char *input = readline("tinydb > ");
        if (is_empty(input)) {
            continue;
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
        char buff[BUFF_SIZE];
        sprintf(buff, "%s", input);
        size_t result = send(sock_fd, buff, BUFF_SIZE, 0);
        if (result == -1) {
            fprintf(stderr, "Send fail.");
            exit(1);
        }
        db_receive(sock_fd);
        add_history(buff);
        free(input);
    }
    close(sock_fd);
    return 0;
}
