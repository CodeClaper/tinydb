#include "data.h"

/*init session*/
void init_session();

/*Generate new session.*/
Session *new_session(int client);

/*Set session to pthread_key_t.*/
void set_session(void *session);

/*Get session from pthread_key_t.*/
Session *get_session();

/* Socket send
 * return true if send successfully, else return false.
 * */
bool db_send(const char *buff);

/* Socket send 'Over' flag,
 * which means the message is over.
 * */
bool db_send_over();

/*destroy session, free the session memory. */
void destroy_session();

/*Delete pthread_key_t*/
void end_session();

