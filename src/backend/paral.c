#include <pthread.h>
#include "mmgr.h"

/* Parallel computing. */
void ParallelCompute(int workerNum, void *task, void *taskArgs[]) {
    pthread_t workers[workerNum];

    StartParallelComputeMode(workers, workerNum);

    /* Assign the task. */
    for (int i = 0; i < workerNum; i++) {
        pthread_create(&workers[i], NULL, task, taskArgs[i]);
    }

    /* Wait all workers. */
    for (int i = 0; i < workerNum; i++) {
        pthread_join(workers[i], NULL);
    }

    EndParallelComputeMode();
}
