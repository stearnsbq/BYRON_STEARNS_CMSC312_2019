#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "queue.hpp"
#include <thread>
#include "mainwindow.h"

class Scheduler
{
public:
    Scheduler();
    //Scheduler(ALGORITHM algo);
    ~Scheduler();
    void addNewProcess(Process Process);
    void start(MainWindow * window, int time, QString unit);
    void run();

private:
    void feedBackQueue();
    void roundRobinProcess(int queueNum, int timeQ);
    void clock(int time, QString unit);
    void processNewQueue();
    void processReadyQueue();
    void processWaitingQueue();
    void round_robin();
    void priority();
    int timeQuantum;
    bool isRunning;

    int processesRan;
    int totalProcesses;
    std::thread clockThread;
    Process runningProcess;
   // ALGORITHM algorithmToUse;
    Queue *readyQueue;
    Queue *newQueue;
    Queue *waitingQueue;
    Queue *topLevel;
    Queue *midLevel;
    Queue *baseLevel;
};
#endif
