#include "data.h"

#define DEFAULT_SPIN_INTERVAL 10
#define SPIN_LOCKED_STATUS 1
#define SPIN_UN_LOCKED_STATUS 0

typedef int s_lock;

/* Acquire spin lock, if fail, it will block. */
void spinLockAcquire(s_lock *lock);

/* Release spin lock. */
void spinLockRelease(s_lock *lock);
