#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <pthread.h>
#include "data.h"
#include "defs.h"
#include "mem.h"
#include "token.h"
#include "input.h"
#include "stmt.h"
#include "free.h"
#include "server.h"
#include "common.h"
#include "misc.h"
#include "log.h"

char *data_dir;
MTable *mtable;

// init variable
void init_variable() {
    data_dir = "/home/zc/data/";
    mtable = sys_malloc(sizeof(MTable));
    mtable->entry_list = sys_malloc(0);
    mtable->num = 0;
}

// print prompt
void print_prompt() { 
    printf("tinydb > "); 
}

int main(void) {
    init_variable();
    log_init(); // init log
    int server_socket = -1;
    int client_secket = -1;
    u_short port = 4080;
    struct sockaddr_in *client_name = sys_malloc(sizeof(struct sockaddr_in));
    socklen_t client_name_len = sizeof(*client_name);
    pthread_t new_thread;
    server_socket = startup(port);
    printf("Tinydb server start up successfully. and listen port %d \n", port);
    while(true) {
        client_secket = accept(server_socket, (struct sockaddr *) client_name, &client_name_len);
        if (client_name_len == -1)
            fatal("Socket accept fail.");
        else
            printf("Client connect successfully.\n");
        if (pthread_create(&new_thread, NULL, (void *)accept_request, (void *)(intptr_t)client_secket) != 0) {
            fatal("Create new thread fail.");
        }
    }
    destroy_log();
    return 0;
}
