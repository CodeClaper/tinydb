#include "log.h"
#include "data.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_key_t key;

//Destruct value
static void key_destructor(void *value) {
    if (value)
        free(value);
} 

//Log init
void log_init() {
    pthread_key_create(&key, key_destructor);
}

//Info
void log_info(char *msg) {

}

//Error
void log_error(char *msg) {
    pthread_setspecific(key, (void *)msg);
#ifdef DEBUG
    fprintf(stderr, "%s\n", msg);
#endif
}

//Error for string format
void log_error_s(char *format, char *s) {
    int len = strlen(format) + strlen(s);
    char *msg = malloc(len);
    memset(msg, 0, len);
    sprintf(msg, format, s);
    pthread_setspecific(key, (void *)msg);
#ifdef DEBUG
    fprintf(stderr, "%s\n", msg);
#endif
}

//Error for string format
void log_error_s_s(char *format, char *s1, char *s2) {
    int len = strlen(format) + strlen(s1) + strlen(s2);
    char *msg = malloc(len);
    memset(msg, 0, len);
    sprintf(msg, format, s1, s2);
    pthread_setspecific(key, (void *)msg);
#ifdef DEBUG
    fprintf(stderr, "%s\n", msg);
#endif
}

//Error for int format
void log_error_d(char *format, int i) {
    int len = strlen(format) + 20;
    char *msg = malloc(len);
    memset(msg, 0, len);
    sprintf(msg, format, i);
    pthread_setspecific(key, (void *)msg);
#ifdef DEBUG
    fprintf(stderr, "%s\n", msg);
#endif
}

//Get current error.
char *get_current_error() {
    return (char *)pthread_getspecific(key); 
}

//Clear error
void clear_error() {
    pthread_key_delete(key);
}
