#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "server.h"
#include "mmu.h"
#include "common.h"
#include "stmt.h"
#include "free.h"
#include "session.h"
#include "log.h"
#include "timer.h"

/* Start up the server. */
int startup(u_short port) {
    int httpd = 0;
    int on = 1;
    size_t buff_size = 65535;
    struct sockaddr_in *address = sys_malloc(sizeof(struct sockaddr_in));
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

/* Accept request.*/
void accept_request(intptr_t client) {
    size_t chars_num;
    char buf[SPOOL_SIZE];
    new_session(client);
    db_log(INFO, "Client ID '%ld' connect successfully.", getpid());
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while((chars_num = recv(client, buf, SPOOL_SIZE - 1, 0)) > 0) {
        buf[chars_num] = '\0';
        execute(buf);   
        if (!db_send_over())
            break;

        gettimeofday(&end, NULL);
        db_log(INFO, "Loop duration: %lfs", time_span(end, start));
        start = end;
    }
    close(client);
    db_log(INFO, "Client ID '%ld' disconnect.", getpid());
    exit(0);
}
