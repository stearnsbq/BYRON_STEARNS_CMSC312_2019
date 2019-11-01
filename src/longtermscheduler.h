#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H
#include "PCB.hpp"
#include "priorityqueue.hpp"
#include "CPU.hpp"
class CPU;
class kernel;
class LongTermScheduler
{
public:
LongTermScheduler();
~LongTermScheduler();
void enqueueProcess(Process p);
void runScheduler();
private:
PriorityQueue * jobQueue;

};

#endif // LONGTERMSCHEDULER_H
