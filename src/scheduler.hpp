#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "queue.hpp"
#include <thread>
#include "mainwindow.h"
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
    void start(MainWindow * window, int time, QString unit);

    void run();

private:
    void rotateProcess();
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
    ALGORITHM algorithmToUse;
    Queue *readyQueue;
    Queue *newQueue;
    Queue *waitingQueue;
};
#endif
