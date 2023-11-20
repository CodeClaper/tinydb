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
#include "session.h"
#include "misc.h"
#include "log.h"

char *data_dir;

// init
static void init() {
    data_dir = "/home/zc/data/";
    init_mem(); // init mmu
    init_session();
}

// end
static void end() {
    end_session();
}

int main(void) {
    init();
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
        if (pthread_create(&new_thread, NULL, (void *)accept_request, (void *)(intptr_t)client_secket) != 0)
            fatal("Create new thread fail.");
    }
    end();
    return 0;
}
