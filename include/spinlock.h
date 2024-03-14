#include "data.h"

#define DEFAULT_SPIN_INTERVAL 10
#define SPIN_LOCKED_STATUS 1
#define SPIN_UN_LOCKED_STATUS 0

typedef int s_lock;

/* Init spin lock. */
void spin_lock_init(s_lock *lock);

/* Acquire spin lock, if fail, it will block. */
void spin_lock_acquire(s_lock *lock);

/* Release spin lock. */
void spin_lock_release(s_lock *lock);
