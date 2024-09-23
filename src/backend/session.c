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
#include "session.h"
#include "data.h"
#include "mmu.h"
#include "log.h"
#include "asserts.h"

#define OVER_FLAG "OVER"  /* Over flag of message. */


static Session inner_session;


/* Init spool. */
static void clearn_up_spool();


/* New session. */
void new_session(int client) {
    inner_session.client = client;
    inner_session.frequency = 0;
    inner_session.volumn = 0;
}


static bool spool_is_full() {
    return inner_session.pindex >= SPOOL_SIZE;
}

/* Init spool. */
static void clearn_up_spool() {
    memset(inner_session.spool, '\0', SPOOL_SIZE);
    inner_session.pindex = 0;
}

/* Store spool. */
static char *store_spool(char *message) {
    size_t len = strlen(message);
    int index = inner_session.pindex + len;
    if (strcmp(OVER_FLAG, message) == 0) {
        if (inner_session.pindex == 0) {
            memcpy(inner_session.spool + inner_session.pindex, message, len); 
            return NULL;
        } else {
            return message;
        }
    } else if (index < SPOOL_SIZE) {
        memcpy(inner_session.spool + inner_session.pindex, message, len); 
        inner_session.pindex = index;
        return NULL;
    } else {
        inner_session.pindex = SPOOL_SIZE;
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
    ssize_t r = -1, s = 0;
    char rbuff[3], sbuff[SPOOL_SIZE];

    /* Initialize send buffer. */
    memset(sbuff, 0, SPOOL_SIZE);

    va_start(ap, format);
    
    /* Assignment send buffer. */
    vsprintf(sbuff, format, ap);
    
    va_end(ap);


    /* Store message into spool. */
    char *left_msg = store_spool(sbuff);

    /* Only when spool is full or OVER FLAG, socket will send the whole spool data. */
    if (!spool_is_full() && strcmp(OVER_FLAG, sbuff) != 0)
        return true;


    /* Check if client close connection, if recv get zero which means client has closed conneciton. */
    if ((r = recv(inner_session.client, rbuff, 3, MSG_PEEK | MSG_DONTWAIT)) != 0 
            && (s = send(inner_session.client, inner_session.spool, SPOOL_SIZE, 0)) > 0) {

        inner_session.volumn += s;
        inner_session.frequency++;

        clearn_up_spool();

        /* If there are left message, continue db_send. */
        if (left_msg) {
            return db_send(left_msg);
        }

        return true;
    }

    return false;
}

/* Socket send 'OVER' flag,
 * which means the message is over.
 * */
bool db_send_over() {
    return db_send(OVER_FLAG);
}

