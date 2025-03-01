#include "buftable.h"
#include "spinlock.h"
#include "mmgr.h"
#include <stdint.h>
#include <string.h>

/* BTable is a hash table. */
static BufferTableEntrySlot *BTable;

typedef unsigned long Hash;

/* Hash the BufferTag. */
static Hash HashBufferTag(BufferTag *tag, Size size) {
    /* Use DJB2 hash alg. */
    unsigned long hash = 5381;
    hash = ((hash << 5) + hash) + tag->blockNum;
    const char *tableName = tag->tableName;
    int c;
    while ((c = *tableName++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

static BufferTableEntry *NewBufferTableEntry(BufferTag *tag, Buffer buffer) {
    switch_shared();
    BufferTableEntry *entry = instance(BufferTableEntry);
    entry->buffer = buffer;
    entry->tag.blockNum = tag->blockNum;
    memcpy(entry->tag.tableName, tag->tableName, MAX_TABLE_NAME_LEN);
    entry->next = NULL;
    switch_local();
    return entry;
}

/* Get Buffer Table slot. */
inline BufferTableEntrySlot *GetBufferTableSlot(BufferTag *tag) {
    Hash hash = HashBufferTag(tag, BUFFER_SLOT_NUM);
    return (BufferTableEntrySlot *)(BTable + hash);
}

/* Create the buffer table.*/
void CreateBufferTable() {
    Size size = BUFFER_SLOT_NUM;
    switch_shared();
    BTable = dalloc(sizeof(BufferTableEntrySlot) * size);
    for (Index i = 0; i < size; i++) {
        BufferTableEntrySlot *header = (BufferTableEntrySlot *)(BTable + i);
        InitRWlock(&header->lock);
    }
    switch_local();
}


/* Lookup for Buffer in entry table. 
 * -------------------------
 * Return the found buffer and -1 if not found. */
Buffer LookupBufferTable(BufferTag *tag) {
    Buffer buffer;
    BufferTableEntrySlot *slot;
    BufferTableEntry *entry;

    buffer = -1;
    slot = GetBufferTableSlot(tag);
    entry = slot->next;

    /* Acquire the rwlock in shared mode.*/
    AcquireRWlock(&slot->lock, RW_READERS);

    /* Loop up the entry table. */
    while (entry != NULL) {
        if (BufferTagEquals(&entry->tag, tag)) {
            buffer = entry->buffer;
            break;
        }
        entry = entry->next;
    }
    /* Release the rwlock. */
    ReleaseRWlock(&slot->lock);
    return buffer;
}


/* Save new BufferTableEntry 
 * ---------------
 * BufferTableEntry link the BufferTag and Buffer. 
 * Note: This <InsertBufferTableEntry> need acquire the rwlock in exclusive mode. 
 * But not acquire itself, and by the caller.
 * */
void InsertBufferTableEntry(BufferTag *tag, Buffer buffer) {
    BufferTableEntrySlot *slot;
    BufferTableEntry *entry;

    slot = GetBufferTableSlot(tag);
    entry = slot->next;
    Assert(slot->lock.mode == RW_WRITER);

    if (entry == NULL) {
        slot->next = NewBufferTableEntry(tag, buffer);
        return;
    }

    /* Find the tail. */
    while (entry->next) {
        entry = entry->next;
    }
    entry->next = NewBufferTableEntry(tag, buffer);
}

/* Delete the BufferTableEntry by tag.
 * ------------
 * Note: This <DeleteBufferTableEntry> need acquire the rwlock in exclusive mode. 
 * But not acquire itself, and by the caller.
 * */
void DeleteBufferTableEntry(BufferTag *tag) {
    BufferTableEntrySlot *slot; 
    BufferTableEntry *pres, *current;

    slot = GetBufferTableSlot(tag);
    current = slot->next;
    Assert(slot->lock.mode == RW_WRITER);

    for (current = slot->next, pres = current; current != NULL; pres = current, current = current->next) {
        if (BufferTagEquals(&current->tag, tag)) {
            if (current == slot->next) 
                slot->next = current->next;
            else 
                pres->next = current->next;
            
            /* Necessary to free the shared memory. */
            switch_shared();
            dfree(current);
            switch_local();
        }
    }
}
