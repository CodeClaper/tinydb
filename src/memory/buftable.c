#include "buftable.h"
#include "spinlock.h"
#include "mmgr.h"
#include <string.h>
#include <time.h>

/* BTable is a hash table. */
static BufferTableEntry *BTable;

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
    memcpy(entry->tag.tableName, tag->tableName,  MAX_TABLE_NAME_LEN);
    entry->pres = NULL;
    entry->next = NULL;
    init_spin_lock(&entry->lock);
    switch_local();
    return entry;
}

/* Get Buffer Table slot. */
static inline BufferTableEntry *GetBufferTableSlot(BufferTag *tag) {
    Hash hash = HashBufferTag(tag, BUFFER_SLOT_NUM);
    return (BufferTableEntry *)(BTable + hash);
}

/* Init the buffer table.*/
void InitBufferTable() {
    switch_shared();
    Size size = sizeof(BufferTableEntry) * BUFFER_SLOT_NUM;
    BTable = dalloc(size);
    switch_local();
}


/* Return Buffer of BufferDesc, 
 * and -1 if not found.*/
Buffer LookupBufferTable(BufferTag *tag) {
    Buffer buffer;
    BufferTableEntry *slot, *current;
    buffer = -1;
    slot = GetBufferTableSlot(tag);
    current = slot;
    acquire_spin_lock(&slot->lock);
    while (current != NULL) {
        if (BufferTagEquals(&current->tag, tag)) {
            buffer = current->buffer;
            break;
        }
        current = current->next;
    }
    release_spin_lock(&slot->lock);
    return buffer;
}


/* Save new BufferTableEntry 
 * which link the BufferTag and Buffer. */
void InsertBufferTableEntry(BufferTag *tag, Buffer buffer) {
    BufferTableEntry *slot, *current;
    slot = GetBufferTableSlot(tag);
    acquire_spin_lock(&slot->lock);
    current = slot;
    while (current->next != NULL) {
        current = current->next;
    }
    if (BufferTagEmpty(current->tag)) {
        memcpy(current->tag.tableName, tag->tableName, MAX_TABLE_NAME_LEN);
        current->tag.blockNum = tag->blockNum;
        current->buffer = buffer;
    } else 
        current->next = NewBufferTableEntry(tag, buffer);
    release_spin_lock(&slot->lock);
}

/* Delete the BufferTableEntry by tag.*/
void DeleteBufferTableEntry(BufferTag *tag) {
    BufferTableEntry *slot, *current;
    slot = GetBufferTableSlot(tag);
    switch_shared();
    acquire_spin_lock(&slot->lock);
    current = slot;
    while (current != NULL) {
        if (BufferTagEquals(&current->tag, tag)) {
            if (current == slot) {
                /* If Current is slot, then check if next exists.
                 * If yes, replace the slot with next and delete the next.
                 * If no, just make the tag empty. in slot. */
                if (current->next != NULL) {
                    BufferTableEntry *next = current->next;
                    memcpy(current->tag.tableName, next->tag.tableName, MAX_TABLE_NAME_LEN);
                    current->tag.blockNum = next->tag.blockNum;
                    current->next = next->next;
                    dfree(next);
                } else 
                    MakeBufferTagEmpty(&current->tag);
            } else {
                BufferTableEntry *pres = current->pres;
                BufferTableEntry *next = current->next;
                pres->next = next;
                if (next != NULL)
                    next->pres = pres;
            }
            break;
        }
        current = current->next;
    }
    release_spin_lock(&slot->lock);
    switch_local();
}
