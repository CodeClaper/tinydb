#include "data.h"

#ifndef XLOG_H
#define XLOG_H

/* XLog Heap Type. */
typedef enum XLogHeapType {
    HEAP_INSERT,
    HEAP_DELETE,
    HEAP_UPDATE_INSERT,
    HEAP_UPDATE_DELETE
} XLogHeapType;

/* XLogEntry */
typedef struct XLogEntry {
    Xid xid;                    /* Transaction Id */
    Refer *refer;               /* Row refer. */
    XLogHeapType type;          /* XLog Head type. */
    struct XLogEntry *next;     /* Next XLogEntry */
} XLogEntry;

/* Record Xlog. */
void RecordXlog(Refer *refer, XLogHeapType type);

/* Update xlog entry refer. */
void UpdateXlogEntryRefer(ReferUpdateEntity *refer_update_entity);

/* Commit Xlog. */
void CommitXlog();

/* Execute rollback. */
void ExecuteRollback();

#endif
