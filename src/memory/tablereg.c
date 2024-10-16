#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "tablereg.h"
#include "mem.h"
#include "utils.h"

static TableRegEntry *regheader;

static void *new_table_reg_entry(char *table_name, pid_t pid);

/* Init tablereg. */
void init_table_reg() {
    regheader = new_table_reg_entry(NULL, 0); 
}

/* Generate new TableRegEntry. */
static void *new_table_reg_entry(char *table_name, pid_t pid) {
    switch_shared();
    TableRegEntry *entry = instance(TableRegEntry);
    if (table_name)
        strcpy(entry->table_name, table_name);
    entry->pid = pid;
    switch_local();
    return entry;
}


/* Get the tail of list of TableRegEntry. */
static void *get_table_reg_tail() {
    TableRegEntry *entry = regheader;
    while(entry->next) {
        entry = entry->next;
    }
    return entry;
}


/* Find the TableRegEntry by table name and pid. */
static void *find_table_reg(char *table_name) {
    TableRegEntry *entry = regheader;
    while((entry = entry->next)) {
        if (streq(entry->table_name, table_name) && entry->pid == getpid())
            return entry;
    }
    return NULL;
}

/* Register new TableRegEntry. */
static void register_table_reg(char *table_name) {
    TableRegEntry *entry = new_table_reg_entry(table_name, getpid());
    TableRegEntry *tail = get_table_reg_tail();
    Assert(tail);
    tail->next = entry;
}

/* Try to register TableRegEntry, 
 * if already exists one, not actually call register_table_reg() */
void try_register_table_reg(char *table_name) {
    TableRegEntry *entry = find_table_reg(table_name);
    if (is_null(entry)) 
        register_table_reg(table_name);
}

/* Destroy TableRegEntry by pid. */
void destroy_table_reg() {
    switch_shared();

    TableRegEntry *current = regheader;
    TableRegEntry *pres = regheader;
    while ((current = current->next) != NULL) {
        if (current->pid == getpid()) {
            pres->next = current->next;
            dfree(current);
        } 
        else 
            pres = current;
    }

    switch_local();
}

/* Check if table shared by other pid. */
bool if_shared_table(char *table_name) {
    TableRegEntry *entry = regheader;
    while((entry = entry->next)) {
        if (streq(entry->table_name, table_name) && entry->pid != getpid())
            return true;
    }
    return false;
}
