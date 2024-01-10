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
#include "mmu.h"
#include "lock.h"
#include "trans.h"
#include "parser.h"
#include "stmt.h"
#include "free.h"
#include "server.h"
#include "common.h"
#include "session.h"
#include "misc.h"
#include "conf.h"
#include "gc.h"
#include "cache.h"
#include "log.h"

/* Conf */
Conf *conf;

/* init */
static void init() {
    /* Initialise memory manager unit. */
    init_mem(); 
    /* Initialise session. */
    init_session();
    /* Initialise lock. */
    init_lock();
    /* Initialise transaction. */
    init_transaction();
    /* Initialise table cache. */
    init_table_cache();
    /* Load configuration. */
    conf = load_conf();
}

/* end */
static void end() {
    end_session();
}

int main(void) {

    init();
    int server_socket = -1;
    int client_secket = -1;
    struct sockaddr_in *client_name = sys_malloc(sizeof(struct sockaddr_in));
    socklen_t client_name_len = sizeof(*client_name);
    pthread_t new_thread, gc_thread;
    server_socket = startup(conf->port);
    db_info("Tinydb server start up successfully and listen port %d.", conf->port);

    /* start gc */
    if (pthread_create(&gc_thread, NULL, (void *)loop_gc, NULL) != 0)
        fatal("Create new thread fail.");

    /* listen */
    while(true) {
        client_secket = accept(server_socket, (struct sockaddr *) client_name, &client_name_len);
        if (client_secket == -1)
            fatal("Socket accept fail.");
        if (pthread_create(&new_thread, NULL, (void *)accept_request, (void *)(intptr_t)client_secket) != 0)
            fatal("Create new thread fail.");
    }
    end();

    return EXIT_SUCCESS;
}
