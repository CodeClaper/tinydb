#include "data.h"


/* Initialise XLOG. */
void init_xlog();

/* Insert into XLogEntry. */
void insert_xlog_entry(Refer *refer, DDLType type) ;

/* Update xlog entry refer. */
void update_xlog_entry_refer(ReferUpdateEntity *refer_update_entity);

/* Commit Xlog. */
void commit_xlog();

/* Execute rollback. */
void execute_roll_back();

