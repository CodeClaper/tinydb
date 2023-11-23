#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data.h"
#include "conf.h"
#include "mem.h"
#include "utils.h"

#define DEFAULT_CONF_FILE "/etc/tinydb.cnf"

/* Read config file. */
char *read_conf(char *key) {
    FILE *file = fopen(DEFAULT_CONF_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Try to open config file in path '%s' fail.\n", DEFAULT_CONF_FILE);
        exit(1);
    }
    char buff[BUFF_SIZE];
    char *p;
    while(!feof(file)) {
        fgets(buff, BUFF_SIZE, file);
        char *line = trim(buff);
        /* Check if commenter line. */
        if (startwith(line, "//") || startwith(line, "#"))
            continue;
        /* Check if has symbol '='. */
        if (strchr(line, '=') == NULL)
            continue;
        /* Check if this line contains key. */
        if (!startwith(line, key))
            continue;
        p = strstr(line, key);
        assert(p);
        p += strlen(key);
        trim(p);
        /* skip '=' */
        p += 1;
        return strdup(trim(p));
    }
    return NULL;
}

/* Load configuration. */
Conf *load_conf() {
    Conf *conf = db_malloc2(sizeof(Conf), "Conf");
    conf->data_dir = read_conf("dir");
    return conf;
}
