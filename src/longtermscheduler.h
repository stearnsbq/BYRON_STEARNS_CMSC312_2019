#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H
#include "PCB.hpp"



class CPU;
class kernel;
class ShortTermScheduler;
class LongTermScheduler
{
public:
LongTermScheduler(ShortTermScheduler * scheduler, int coreNum);
~LongTermScheduler();
void enqueueProcess(Process p);
void runScheduler();
private:
ShortTermScheduler * scheduler;
int coreNum;


};

#endif // LONGTERMSCHEDULER_H
