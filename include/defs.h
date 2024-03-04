#include <setjmp.h>
#include "data.h"

#ifndef DEFS_H
#define DEFS_H
extern Conf *conf;  /* Configuration */
extern jmp_buf errEnv; /* jmp_buf for error. */
#endif
