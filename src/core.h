#ifndef CORE_H
#define CORE_H
#include <thread>
#include "shorttermscheduler.h"
#include "longtermscheduler.h"
#include "mutex.h"

class Core
{
public:
Core(int coreNumber);
~Core();
void start(int time, QString unit);
Process runningProcess;
private:
int coreNum;
void run(int time, QString unit);
void cycle();
void sleep();
void executeOperation();
void iO();
void calculate();
void criticalSection();
void yield();
void fork();
void out();
void send();
void recieve();
ShortTermScheduler * shortTerm;
LongTermScheduler * longTerm;

mutex mutexLock;
int time;
QString unit;
short ltTimer;

};

#endif // CORE_H
