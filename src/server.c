#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "mmu.h"
#include "common.h"
#include "misc.h"
#include "stmt.h"
#include "free.h"
#include "session.h"
#include "log.h"

/* Start up the server. */
int startup(u_short port) {
    int httpd = 0;
    int on = 1;
    struct sockaddr_in *address = sys_malloc(sizeof(struct sockaddr_in));
    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        fatal("Create socket fail.");
    memset(address, 0, sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) {
        fatal("Set socket option fail.");
    }
    if (bind(httpd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        fatal("Bind socket fail.");
    }
    if (listen(httpd, 10) < 0) {
        fatal("Socket listen fail.");
    }
    return httpd;
}

/* Accept request.*/
void accept_request(void *arg) {
    int client = (intptr_t) arg;
    size_t chars_num;
    char buf[1024];
    Session *session = new_session(client);
    set_session(session);
    db_info("Client ID '%ld' connect successfully.\n", pthread_self());
    while((chars_num = recv(client, buf, 1024, 0)) > 0) {
        buf[chars_num] = '\0';
        statement(buf);   
        if (!db_send_over())
            break;
    }
    close(client);
    destroy_session();
    db_info("Client ID '%ld' disconnect.\n", pthread_self());
}
