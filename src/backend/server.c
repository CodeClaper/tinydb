#include <bits/types/struct_timeval.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "server.h"
#include "defs.h"
#include "mem.h"
#include "common.h"
#include "stmt.h"
#include "free.h"
#include "session.h"
#include "log.h"
#include "auth.h"
#include "timer.h"
#include "banner.h"
#include "mctx.h"
#include "asctx.h"

/* Start up the server. */
int startup(u_short port) {
    int httpd = 0;
    int on = 1;
    size_t buff_size = SPOOL_SIZE;
    struct sockaddr_in *address = dalloc(sizeof(struct sockaddr_in));
    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        db_log(PANIC, "Create socket fail.");
    memset(address, 0, sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = htonl(INADDR_ANY);

    /* SO_REUSEADDR */
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) 
        db_log(PANIC, "Set socket SO_REUSEADDR option fail.");

    /* Bind */
    if (bind(httpd, (struct sockaddr *)address, sizeof(*address)) < 0) 
        db_log(PANIC, "Bind socket fail.");

    /* SO_RCVBUF */
    if ((setsockopt(httpd, SOL_SOCKET, SO_RCVBUF, &buff_size, sizeof(buff_size))) < 0) 
        db_log(PANIC, "Set socket SO_RCVBUF option fail.");

    /* SO_SNDBUF */
    if ((setsockopt(httpd, SOL_SOCKET, SO_SNDBUF, &buff_size, sizeof(buff_size))) < 0) 
        db_log(PANIC, "Set socket SO_SNDBUF option fail.");

    /* Listen */
    if (listen(httpd, 10) < 0) 
        db_log(PANIC, "Socket listen fail.");

    return httpd;
}


/* Auth client. */
static bool auth_request(intptr_t client) {
    char buf[SPOOL_SIZE];
    char sbuf[SPOOL_SIZE];
    
    /* Intialize. */
    bzero(buf, SPOOL_SIZE);
    bzero(sbuf, SPOOL_SIZE);

    size_t chars_num = recv(client, buf, SPOOL_SIZE, 0);
    if (chars_num > 0) {
        buf[chars_num] = '\0';
        /* Banner. */
        bool pass = auth(buf);
        if (pass) 
            sprintf(sbuf, LOG);
        else
            sprintf(sbuf, "No access.");

        size_t s = send(client, sbuf, SPOOL_SIZE, 0);
        if (s == -1) 
            db_log(ERROR, "Try to send %s fail, %s.", sbuf, strerror(errno));

        return pass;
    }

    return false;
}


/* For loop request. */
static void loop_request(intptr_t client) {
    size_t chars_num;
    char buf[SPOOL_SIZE];
    bzero(buf, SPOOL_SIZE);
    new_session(client);
    db_log(INFO, "Client ID '%ld' connect successfully.", getpid());
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while((chars_num = recv(client, buf, SPOOL_SIZE, 0)) > 0) {
        buf[chars_num] = '\0';
        execute(buf);
        bzero(buf, SPOOL_SIZE);
        if (!db_send_over())
            break;
        gettimeofday(&end, NULL);
        db_log(INFO, "Loop duration: %lfs", time_span(end, start));
        start = end;
        MemoryContextReset(MASTER_MEMORY_CONTEXT);
    }
    db_log(INFO, "Client ID '%ld' disconnect.", getpid());
}

/* Accept request.*/
void accept_request(intptr_t client) {
    MASTER_MEMORY_CONTEXT = AllocSetMemoryContextCreate(TOP_MEMORY_CONTEXT, "MasterMemoryContext", DEFAULT_MAX_BLOCK_SIZE);
    MemoryContextSwitchTo(MASTER_MEMORY_CONTEXT);
    /* Auth login message. */
    if (auth_request(client))
        loop_request(client);
    
    /* Quite */
    close(client);
    exit(0);
    MemoryContextDelete(MASTER_MEMORY_CONTEXT);
}
