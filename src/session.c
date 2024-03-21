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
#include "asserts.h"

#define OVER_FLAG "OVER"  /* Over flag of message. */
#define SPOOL_SIZE 4096   /* Spool buffer size. */


static pthread_key_t key; /* Pthread key to store session. */

static char spool[SPOOL_SIZE]; /* Store messsage pool. */
static int sindex;             /* Current spool index. */

/* Init spool. */
static void init_spool();

/* Initialize session. */
void init_session() {
    pthread_key_create(&key, NULL);
    init_spool();
}

/* Generate new session. */
Session *new_session(int client) {
    Session *session = db_malloc(sizeof(Session), SDT_SESSION);
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

/* Init spool. */
static void init_spool() {
    sindex = 0;
    memset(spool, 0, SPOOL_SIZE);
}

/* Store spool. */
static char *store_spool(char *message) {
    size_t len = strlen(message);
    int index = sindex + len;
    if (index <= SPOOL_SIZE) {
        memcpy(spool + sindex, message, len); 
        sindex = index;
        return NULL;
    } else {
        size_t sub_len = SPOOL_SIZE - sindex;
        memcpy(spool + sindex, message, sub_len); 
        sindex = sindex + sub_len;
        return message + sub_len;
    }
}

/* Socket send message.
 * return true if send successfully, else return false. */
bool db_send(const char *format, ...) {
    if (format == NULL)
        return false;

    assert_true(strlen(format) < BUFF_SIZE, "Overflow");

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
    
    va_end(ap);

    /*Get session*/
    session = get_session(); 

    /* Check if client close connection, if recv get zero which means client has closed conneciton. */
    if (session != NULL && (r = recv(session->client, rbuff, 3, MSG_PEEK | MSG_DONTWAIT)) != 0 && (s = send(session->client, sbuff, BUFF_SIZE, 0)) > 0) {
        session->volumn += s;
        session->frequency++;
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

