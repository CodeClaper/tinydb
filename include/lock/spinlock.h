#include "data.h"

#define DEFAULT_SPIN_INTERVAL 10
#define SPIN_LOCKED_STATUS 1
#define SPIN_UN_LOCKED_STATUS 0

typedef int s_lock;


/* Init spin lock. */
void init_spin_lock(volatile s_lock *lock);

/* Acquire spin lock, if fail, it will block. */
void acquire_spin_lock(volatile s_lock *lock);

/* Release spin lock. */
void  release_spin_lock(volatile s_lock *lock);

/* Wait for spin lock released. */
void wait_for_spin_lock(volatile s_lock *lock);
