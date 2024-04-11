#include <stdbool.h>
#include <stddef.h>
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
#include "log.h"
#include "asserts.h"

#define OVER_FLAG "OVER"  /* Over flag of message. */

static pthread_key_t key; /* Pthread key to store session. */


/* Init spool. */
static void clearn_up_spool();

/* Initialize session. */
void init_session() {
    pthread_key_create(&key, NULL);
}

/* Generate new session. */
Session *new_session(int client) {
    Session *session = instance(Session);
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

static bool spool_is_full(Session *session) {
    return session->pindex >= SPOOL_SIZE;
}

/* Init spool. */
static void clearn_up_spool(Session *session) {
    memset(session->spool, '\0', SPOOL_SIZE);
    session->pindex = 0;
}

/* Store spool. */
static char *store_spool(Session *session, char *message) {
    size_t len = strlen(message);
    int index = session->pindex + len;
    if (strcmp(OVER_FLAG, message) == 0) {
        if (session->pindex == 0) {
            memcpy(session->spool + session->pindex, message, len); 
            return NULL;
        } else {
            return message;
        }
    } else if (index < SPOOL_SIZE) {
        memcpy(session->spool + session->pindex, message, len); 
        session->pindex = index;
        return NULL;
    } else {
        session->pindex = SPOOL_SIZE;
        return message;
    }
}

/* Socket send message.
 * return true if send successfully, else return false. */
bool db_send(const char *format, ...) {
    if (format == NULL)
        return false;

    assert_true(strlen(format) < SPOOL_SIZE, "Overflow");

    va_list ap;
    size_t size ;
    ssize_t r = -1, s = 0;
    Session *session;
    char rbuff[3], sbuff[SPOOL_SIZE];

    /* Initialize send buffer. */
    memset(sbuff, 0, SPOOL_SIZE);

    va_start(ap, format);
    
    /* Assignment send buffer. */
    vsprintf(sbuff, format, ap);
    
    va_end(ap);

    /*Get session*/
    session = get_session(); 

    if (session == NULL) {
        db_log(ERROR, "Not found session");
        return false;
    }

    /* Store message into spool. */
    char *left_msg = store_spool(session, sbuff);

    /* Only when spool is full or OVER FLAG, socket will send the whole spool data. */
    if (!spool_is_full(session) && strcmp(OVER_FLAG, sbuff) != 0)
        return true;


    /* Check if client close connection, if recv get zero which means client has closed conneciton. */
    if ((r = recv(session->client, rbuff, 3, MSG_PEEK | MSG_DONTWAIT)) != 0 
        && (s = send(session->client, session->spool, SPOOL_SIZE, 0)) > 0) {
            session->volumn += s;
            session->frequency++;

            clearn_up_spool(session);

            /* If there are left message, continue db_send. */
            if (left_msg) {
                return db_send(left_msg);
            }

            return true;
    }

    /* If detect that client has closed conneciton, destroy the session. */
    if (r == 0 || s < 0) 
        destroy_session(); 

    return false;
}

/* Socket send 'OVER' flag,
 * which means the message is over.
 * */
bool db_send_over() {
    return db_send(OVER_FLAG);
}

/* Delete pthread_key_t. */
void end_session() {
    pthread_key_delete(key);
}

