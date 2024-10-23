#include <setjmp.h>
#include "data.h"
#include "mctx.h"

#ifndef DEFS_H
#define DEFS_H
extern Conf *conf;  /* Configuration */
extern jmp_buf errEnv; /* jmp_buf for error. */

extern MemoryContext CURRENT_MEMORY_CONTEXT;
extern MemoryContext TOP_MEMORY_CONTEXT;
extern MemoryContext MESSAGE_MEMORY_CONTEXT;
#endif
