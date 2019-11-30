#ifndef KERNEL_H
#define KERNEL_H
#include "mainwindow.h"
#include <vector>
#include <mutex>
#include <queue>
#include "priorityqueue.hpp"
#include <string>

class CPU;
class MainWindow;
class pagetable;

class kernel
{
public:

static kernel& getInstance(){     // make this singleton because I only ever need one instance of kernel

    static kernel instance;
    return instance;

}

kernel(kernel const&) = delete;
void operator=(kernel const&) = delete;
void swapIn(Process p);
void schedule(); // runs the schedulers
void newProcess(Process& p);
std::vector<Process > getListOfProcesses();
void updateProcessTable( Process p);
bool isFinished();
MainWindow * window;
void IOPreempt(Process p);
Process getNextProcessInPool();
bool isJobPoolEmpty();
void shutdown();
bool shutDown;
private:
kernel();
~kernel(){
}
bool compare(Process& p1, Process&p2);
pagetable * pTable;
int pidCounter = 0;
unsigned int pageSize; // size of each page
unsigned int longTermTimer; // time before long term runs
std::vector<Process > processTable;
std::priority_queue<Process, std::vector<Process> > jobPool;
std::mutex jobPoolMutex;
std::mutex processTableMutex;


};

#endif // KERNEL_H
