#ifndef SHORTTERMSCHEDULER_H
#define SHORTTERMSCHEDULER_H
#include "queue.hpp"
#include "CPU.hpp"
enum ALGORITHM
{
    ROUND_ROBIN,
    PRIORITY_SCHEDULING,
    MULTILEVEL_FEEDBACK_QUEUE,
};


class ShortTermScheduler
{

public:
ShortTermScheduler(ALGORITHM algoToUse);
ShortTermScheduler();
~ShortTermScheduler();
void runScheduler();
void enqueueProcess(Process p);
private:
Queue * readyQueue;     // used both for RR (tq of 20) / Priority and the top queue for Multilevel feedback queue (RR of time quantum 8)
Queue * midLevel;     // time quantum of 16
Queue * baseLevel;     // time quantum of 20
void roundRobin();
void roundRobinProcess(int queue, int timeQ);
void priority();
void feedBackQueue();
int timeQuantum;
ALGORITHM algorithmToUse;
};

#endif // SHORTTERMSCHEDULER_H
