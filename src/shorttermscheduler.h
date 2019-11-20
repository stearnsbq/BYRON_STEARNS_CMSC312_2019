#ifndef SHORTTERMSCHEDULER_H
#define SHORTTERMSCHEDULER_H
#include "queue.hpp"
#include "mutex.h"
#include "dispatcher.h"

enum ALGORITHM
{
    ROUND_ROBIN,
    PRIORITY_SCHEDULING,
    MULTILEVEL_FEEDBACK_QUEUE,
};


enum QUEUE_TYPE {
    WAITING, READY_Q, MID, BASE
};

class Core;
class Dispatcher;
class ShortTermScheduler
{

public:
ShortTermScheduler(ALGORITHM algoToUse, Core & parent);
ShortTermScheduler();
~ShortTermScheduler();
void setAlgorithm(ALGORITHM algoToUse);
void runScheduler();
void enqueueProcess(Process p, QUEUE_TYPE queue);
private:
mutex * mutexLock;
Queue * readyQueue;     // used both for RR (tq of 20) / Priority and the top queue for Multilevel feedback queue (RR of time quantum 8)
Queue * midLevel;     // time quantum of 16
Queue * baseLevel;     // time quantum of 20
Queue * waitingQueue;
Core & parent;
Dispatcher * dp;
void roundRobin();
void roundRobinProcess(int queue, int timeQ);
void processWaitingQueue();
void priority();
void feedBackQueue();
int timeQuantum;
ALGORITHM algorithmToUse;
};

#endif // SHORTTERMSCHEDULER_H
