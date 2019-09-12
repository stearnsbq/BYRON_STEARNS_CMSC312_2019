#include "../structures/queue.h"
typedef struct Scheduler
{
    int quantum;
    int currentTime;
    ProcessBlock *runningProcess;
    ProcessBlock *processTable;
    Queue *readyQueue;

} Scheduler;

void runProcess(Scheduler *scheduler);
