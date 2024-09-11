#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "data.h"
#include "defs.h"
#include "mmu.h"
#include "mem.h"
#include "trans.h"
#include "xlog.h"
#include "parser.h"
#include "stmt.h"
#include "free.h"
#include "server.h"
#include "common.h"
#include "session.h"
#include "conf.h"
#include "gc.h"
#include "refer.h"
#include "cache.h"
#include "buffer.h"
#include "fdesc.h"
#include "tablelock.h"
#include "log.h"
#include "shmem.h"
#include "lomem.h"
#include "tablereg.h"


Conf *conf; /* Conf */
jmp_buf errEnv; /* jmp_buf for error. */

static void sigchild();

/* DB Start. */
static void db_start() {

    /* Initialise shmem. */
    init_shmem();

    /* Initialise memory manger. */
    init_mem();

    /* Initialise memory manager unit. */
    init_mmu();

    /* Initialise tablereg. */
    init_table_reg();

    /* Initialise fesc.*/
    init_fdesc();

    /* Initialise transaction. */
    init_trans();

    /* Initialise xlog. */
    init_xlog();

    /* Initialise table cache. */
    init_table_cache();

    /* Initialise table buffer. */
    init_table_buffer();

    /* Initialise refer. */
    init_refer();

    /* Initialise table lock. */
    init_table_lock();

    /* Load configuration. */
    conf = load_conf();
}

/* DB Run. */
static void db_run() {
    int server_socket = -1;
    int client_secket = -1;
    struct sockaddr_in *client_name = sys_malloc(sizeof(struct sockaddr_in));
    socklen_t client_name_len = sizeof(*client_name);

    /* Start up server. */
    server_socket = startup(conf->port);
    db_log(INFO, "Tinydb server start up successfully and listen port %d.", conf->port);

    /* Listen client connecting. */
    while(true) {
        client_secket = accept(server_socket, (struct sockaddr *) client_name, &client_name_len);
        if (client_secket == -1)
            db_log(PANIC, "Socket accept fail.");
        
        signal(SIGCHLD, sigchild);

        /* Create new child process. */
        pid_t pid = fork();
        if (pid < 0) 
            db_log(PANIC, "Create new child process fail.");
        else if (pid == 0)
            accept_request((intptr_t)client_secket);
        else
            close(client_secket);
    }
}

/* DB End */
static void db_end() {
}

static void sigchild() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

/* The main entry. */
int main(void) {
    db_start();
    db_run();
    db_end();
    return EXIT_SUCCESS;
}
