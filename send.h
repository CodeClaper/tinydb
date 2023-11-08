#include "data.h"

//init send
void init_send();

// set socket client value
void set_client(void *client);

// get socket client value
int get_client();

// socket send
bool db_send(const char *buff);

// soccket send over flag
bool db_send_over();

//destroy log.
void destroy_send();

