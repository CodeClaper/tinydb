#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "data.h"
#include "conf.h"
#include "mmu.h"
#include "utils.h"

#define DEFAULT_CONF_FILE "/etc/tinydb.cnf"

/* Read config file. */
char *read_conf(char *title, char *key) {
    FILE *file = fopen(DEFAULT_CONF_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Try to open config file in path '%s' fail.\n", DEFAULT_CONF_FILE);
        exit(1);
    }
    char buff[BUFF_SIZE];
    char *p;
    bool inBlock;
    while(!feof(file)) {
        fgets(buff, BUFF_SIZE, file);
        char *line = trim(buff);
        /* Check if commenter line. */
        if (startwith(line, "//") || startwith(line, "#"))
            continue;
        /* Check if the title */
        if (startwith(line, "[") && startwith(line + 1, title)) {
            inBlock = true;    
            continue;
        }
        /* If not in the title block, skip it. */
        if (!inBlock) continue;
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
    fprintf(stderr, "Not found [%s].[%s] in configuration file.\n", title, key);
    exit(EXECUTE_FAIL);
}

/* Load configuration. */
Conf *load_conf() {
    Conf *conf = db_malloc2(sizeof(Conf), "Conf");
    conf->data_dir = read_conf("data", "dir");
    conf->port = (ushort)atoi(read_conf("base", "port"));
    return conf;
}
