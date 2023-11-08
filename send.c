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

static pthread_key_t key;

//init send
void init_send() {
    pthread_key_create(&key, NULL);
}

// set socket client value
void set_client(void* client) {
    pthread_setspecific(key, client);
}
// get socket client value
int get_client() {
    void *arg = pthread_getspecific(key);
    return (intptr_t) arg;
}

/* Socket send
 * return true if send successfully, else return false.
 * */
bool db_send(const char *buff) {
    if (buff == NULL)
        return false;
    int client; size_t size;
    client = get_client(); // get socket client
    size = strlen(buff) + 1; 
    if (send(client, &size, sizeof(size), 0) > 0) {
        if (send(client, buff, size, 0) > 0)
            return true;
    }
    return false;
}

// soccket send over flag
bool db_send_over() {
    return db_send("Over");
}

//destroy log.
void destroy_send() {
    pthread_key_delete(key);
}

