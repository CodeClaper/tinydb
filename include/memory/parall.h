
typedef void (*PARALLEL_TASK) (void *args);

typedef enum ComputeMode {
    NORMAL_COMPUTE,
    PARALLEL_COMPUTE
} ComputeMode;

typedef struct TaskEntry {
    PARALLEL_TASK task;
    void *taskArg;
    struct TaskEntry *next;
} TaskEntry;


/* Get current ComputeMode. */
ComputeMode GetComputeMode();

/* Parallel computing. */
void ParallelCompute(int workerNum, int taskNum, PARALLEL_TASK task, void *taskArgs[]);

