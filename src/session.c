#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "data.h"
#include "mem.h"
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
 * return true if send successfully, else return false.
 * */
bool db_send(const char *msg) {
    if (msg == NULL)
        return false;
    size_t size ;
    ssize_t r = 0, s = 0, session_size = 0;
    Session *session;
    char buff[3];
    size = strlen(msg) + 1; 
    session = get_session(); /*Get session*/

    /* Check if client close connection, if recv return zero which means client close conneciton. */
    r = recv(session->client, buff, 3, MSG_PEEK | MSG_DONTWAIT);
    if (r != 0 && (s = send(session->client, &size, sizeof(size), 0)) > 0) {
        if (session != NULL && (session_size = send(session->client, msg, size, 0)) > 0) {
            session->volumn += session_size;
            session->frequency++;
            return true;
        }
    }
    /* If detect that client has closed conneciton, destroy the session. */
    if (r == 0) 
        destroy_session(); 
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

