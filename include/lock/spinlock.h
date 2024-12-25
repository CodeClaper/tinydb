#include "data.h"

#define DEFAULT_SPIN_INTERVAL 10
#define SPIN_LOCKED_STATUS 1
#define SPIN_UN_LOCKED_STATUS 0

typedef int s_lock;

#if defined(__x86_64__) || defined(__i386__)
    #define PAUSE() __asm__ volatile("pause\n": : : "memory")
#elif defined(__arm__) || defined(__aarch64__)
    #define PAUSE() __asm__ volatile("yield" ::: "memory")
#else
    #define PAUSE() ((void)0)
#endif


/* Lock spin. */
int lock_spin(uint32_t cnt);

/* Lock sleep. */
void lock_sleep (int cnt);

/* Init spin lock. */
void init_spin_lock(volatile s_lock *lock);

/* Acquire spin lock, if fail, it will block. */
void acquire_spin_lock(volatile s_lock *lock);

/* Release spin lock. */
void release_spin_lock(volatile s_lock *lock);

/* Wait for spin lock released. */
void wait_for_spin_lock(volatile s_lock *lock);
