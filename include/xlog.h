#include "data.h"
#include <stdint.h>

typedef struct XLogEntity {
    char *LSN;      /* Log Sequence Number */
    int64_t x_id;   /* Transaction Id */
}XLogEntity;
