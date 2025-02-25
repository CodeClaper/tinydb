#include "bufmgr.h"

typedef struct BufferTableEntry {
    BufferTag tag;
    Buffer buffer;
    s_lock lock;
    struct BufferTableEntry *pres;
    struct BufferTableEntry *next;
} BufferTableEntry;


/* Init the buffer table.*/
void InitBufferTable();


/* Return Buffer of BufferDesc, 
 * and -1 if not found.*/
Buffer LookupBufferTable(BufferTag *tag);


/* Save new BufferTableEntry 
 * which link the BufferTag and Buffer. */
void InsertBufferTableEntry(BufferTag *tag, Buffer buffer);


/* Delete the BufferTableEntry by tag.*/
void DeleteBufferTableEntry(BufferTag *tag);


