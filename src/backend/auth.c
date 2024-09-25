#include <stdbool.h>
#include <stdio.h>
#include "auth.h"
#include "defs.h"
#include "utils.h"

/* Auth the login message. */
bool auth(char *message) {
    char buf[BUFF_SIZE];
    sprintf(buf, "%s/%s", conf->account, conf->password);
    return streq(buf, message);
}

