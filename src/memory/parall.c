#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "data.h"
#include "parall.h"
#include "c.h"
#include "mmgr.h"
#include "mctx.h"
#include "log.h"
#include "spinlock.h"

static ComputeMode mode = NORMAL_COMPUTE;

static TaskEntry *taskQueue;

static s_lock qLock = SPIN_UN_LOCKED_STATUS;

/* Get current ComputeMode. */
ComputeMode GetComputeMode() {
    return mode;
}

void SwitchToParallelCompute() {
    mode = PARALLEL_COMPUTE;
}

void SwitchToNormalCompute() {
    mode = NORMAL_COMPUTE;
}

static TaskEntry *GetTaskQueueTail() {
    TaskEntry *task = taskQueue;
    while (task->next != NULL) {
        task = task->next;
    }
    return task;
}

static void RegisterTaskQueue(PARALLEL_TASK task, void *taskArg) {
    TaskEntry *taskEntry = instance(TaskEntry);
    taskEntry->task = task;
    taskEntry->taskArg = taskArg;
    taskEntry->next = NULL;
    if (taskQueue == NULL)
        taskQueue = taskEntry;
    else {
        TaskEntry *tail = GetTaskQueueTail();
        tail->next = taskEntry;
    }
}

static TaskEntry *AssignTask() {
    acquire_spin_lock(&qLock);
    if (taskQueue == NULL) {
        release_spin_lock(&qLock);
        return NULL;
    }
    else {
        TaskEntry *task = taskQueue;
        taskQueue = taskQueue->next;
        release_spin_lock(&qLock);
        return task;
    }
}

static void TaskProxy() {
    TaskEntry *task;
    while ((task = AssignTask()) != NULL) {
        task->task(task->taskArg);
    }
}

/* Parallel computing. */
void ParallelCompute(int workerNum, int taskNum, PARALLEL_TASK task, void *taskArgs[]) {
    
    db_log(DEBUGER, "Start parall computing, %d workers with %d tasks.", 
           workerNum, taskNum);

    pthread_t workers[workerNum];

    /* Register task. */
    for (int i = 0; i < taskNum; i++) {
        RegisterTaskQueue(task, taskArgs[i]);
    }

    RegisterWorkers(workers, workerNum);
    RegisterContextRecorders(workerNum,  workers);


    SwitchToParallelCompute();

    /* Assign the task. */
    for (int i = 0; i < workerNum; i++) {
        pthread_create(&workers[i], NULL, (void *)&TaskProxy, NULL);
    }

    /* Wait all workers. */
    for (int i = 0; i < workerNum; i++) {
        pthread_join(workers[i], NULL);
    }
    
    SwitchToNormalCompute();

    db_log(DEBUGER, "End parall computing.");
}

