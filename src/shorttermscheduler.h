#ifndef SHORTTERMSCHEDULER_H
#define SHORTTERMSCHEDULER_H
#include "queue.hpp"
#include "mutex.h"
#include <queue>
#include <mutex>

enum ALGORITHM
{
    MULTILEVEL_FEEDBACK_QUEUE,
    ROUND_ROBIN,
    PRIORITY_SCHEDULING,

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
Process determineProcessForMigrate();
int totalProcesses;
private:
mutex * mutexLock;
std::mutex _migrateLock;
std::priority_queue<Process, std::vector<Process> > readyQueue;     // used both for RR (tq of 20) / Priority and the top queue for Multilevel feedback queue (RR of time quantum 8)
std::priority_queue<Process, std::vector<Process> > midLevel;     // time quantum of 16
std::priority_queue<Process, std::vector<Process> > baseLevel;     // time quantum of 20
std::queue<Process> waitingQueue;
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
