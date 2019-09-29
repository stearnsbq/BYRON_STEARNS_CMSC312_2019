#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "queue.hpp"
#include <thread>

enum ALGORITHM
{
    ROUND_ROBIN,
    PRIORITY_SCHEDULING,
    MULTILEVEL_QUEUE,
};

class Scheduler
{
public:
    Scheduler(int timeqc);
    Scheduler();
    ~Scheduler();
    void addNewProcess(Process Process);
    void addReadyProcess(Process Process);
    Process getNextReadyProcess();
    void start();

    void run();

private:
    void rotateProcess();
    void clock();
    void processNewQueue();
    void processReadyQueue();
    void processWaitingQueue();
    void round_robin();
    void priority();
    int timeQuantum;
    std::thread clockThread;
    Process runningProcess;
    ALGORITHM algorithmToUse;
    Queue *readyQueue;
    Queue *newQueue;
    Queue *waitingQueue;
};
#endif
