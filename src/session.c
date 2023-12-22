#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "data.h"
#include "mmu.h"
#include "misc.h"
#include "y.tab.h"

static pthread_key_t key;


/* Initialize session. */
void init_session() {
    pthread_key_create(&key, NULL);
}

/* Generate new session. */
Session *new_session(int client) {
    Session *session = db_malloc2(sizeof(Session), "Session");
    session->client = client;
    session->frequency = 0;
    session->volumn = 0;
    return session;
}

/* Set session to pthread_key_t. */
void set_session(void *session) {
    pthread_setspecific(key, session);
}

/* Get session from pthread_key_t. */
Session *get_session() {
    return pthread_getspecific(key);
}

/* Destroy session, free the session memory. */
void destroy_session() {
    Session *session = get_session();
    db_free(session);
    set_session(NULL);
}

/* Socket send message.
 * First send message size before sending the message.
 * So that, client can prepare enough large buffer to store the message.
 * return true if send successfully, else return false. */
bool db_send(const char *format, ...) {
    if (format == NULL)
        return false;
    va_list ap;
    size_t size ;
    ssize_t r = -1, s = 0;
    Session *session;
    char rbuff[3], sbuff[BUFF_SIZE];

    /* Initialize send buffer. */
    memset(sbuff, 0, BUFF_SIZE);

    va_start(ap, format);
    
    /* Assignment send buffer. */
    vsprintf(sbuff, format, ap);

    /*Get session*/
    session = get_session(); 

    /* Check if client close connection, if recv get zero which means client has closed conneciton. */
    if (session != NULL && (r = recv(session->client, rbuff, 3, MSG_PEEK | MSG_DONTWAIT)) != 0 && (s = send(session->client, sbuff, BUFF_SIZE, 0)) > 0) {
        session->volumn += s;
        session->frequency++;
        va_end(ap);
        return true;
    }

    /* If detect that client has closed conneciton, destroy the session. */
    if (r == 0 || s < 0) 
        destroy_session(); 
    va_end(ap);
    return false;
}

/* Socket send 'OVER' flag,
 * which means the message is over.
 * */
bool db_send_over() {
    return db_send("OVER");
}


/* Delete pthread_key_t. */
void end_session() {
    pthread_key_delete(key);
}

