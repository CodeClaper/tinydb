/**
* ================================= The Garbage Collector (GC) ===================================================
* The GC module is intended to collecte the deleted rows and clean up the unused disk.
* Usually, GC works in the deamon thread, and loop interval scanning.
* GC only starts working on the table only if there are no transactions on the table.
* When GC working on the table, it will lock the table, any transaction that trying to write the table will block.
* =================================================================================================================
*/

#include <unistd.h>
#include "data.h"
#include "trans.h"

void db_gc() {
    
    /* Loop scanning. */
    while(true) {
        sleep(10); /* Sleep 10s. */

    }
}
