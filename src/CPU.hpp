#ifndef CPU_H
#define CPU_H
#include "mainmemory.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "kernel.h"
#include "longtermscheduler.h"
#include "shorttermscheduler.h"
#include <QString>

class CPU
{
private:
CPU();
~CPU();
mainmemory *memory;
int clockTime;
bool isRunning;
int timeQuantum;
std::thread clock_thread;
void cycle();
void run(int time, QString unit);
Process runningProcess;

public:

static CPU& getInstance(){     // make this singleton because I only ever need one instance of CPU

    static CPU instance;

    return instance;

}

CPU(CPU const&) = delete;     // prevents possible insts
void operator=(CPU const&) = delete;
void setTimeQ(int time);
void start(int time, QString unit);
int getTimeQ();
void setIsRunning(bool val);
mainmemory * getMemory();
long long availableMemory();
Process& getRunningProcess();
void setRunningProcess(Process p);
};

#endif
