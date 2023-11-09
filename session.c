#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include "data.h"
#include "mem.h"

static pthread_key_t key;


/*init session*/
void init_session() {
    pthread_key_create(&key, NULL);
}

/*Generate new session*/
Session *new_session(int client) {
    Session *session = db_malloc2(sizeof(Session), "Session");
    session->client = client;
    session->frequency = 0;
    session->volumn = 0;
    return session;
}


/*Set session to pthread_key_t.*/
void set_session(void *session) {
    pthread_setspecific(key, session);
}


/*Get session from pthread_key_t.*/
Session *get_session() {
    return pthread_getspecific(key);
}

/* Socket send
 * return true if send successfully, else return false.
 * */
bool db_send(const char *buff) {
    if (buff == NULL)
        return false;
    size_t size, session_size;
    Session *session;
    size = strlen(buff) + 1; 
    session = get_session(); /*Get session*/
    if (send(session->client, &size, sizeof(size), 0) > 0) {
        if ((session_size = send(session->client, buff, size, 0)) > 0) {
            session->volumn += session_size;
            session->frequency++;
            return true;
        }
    }
    return false;
}

/* Socket send 'Over' flag,
 * which means the message is over.
 * */
bool db_send_over() {
    return db_send("Over");
}

/*destroy session, free the session memory. */
void destroy_session() {
    Session * session = get_session();
    db_free(session);
}

/*Delete pthread_key_t*/
void end_session() {
    pthread_key_delete(key);
}

