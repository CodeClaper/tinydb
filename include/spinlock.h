#include "data.h"

typedef int s_lock;

/* Acquire spin lock, if fail, it will block. */
void spinLockAcquire(s_lock *lock);

/* Release spin lock. */
void spinLockRelease(s_lock *lock);
