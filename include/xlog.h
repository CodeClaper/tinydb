#include "data.h"


/* Initialise XLOG. */
void init_xlog();

/* Insert into XLogEntry. */
void insert_xlog_entry(Refer *refer, DDLType type) ;

/* Commit Xlog. */
void commit_xlog();

/* Execute rollback. */
void execute_roll_back();

