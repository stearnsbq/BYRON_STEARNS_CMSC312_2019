#ifndef KERNEL_H
#define KERNEL_H
#include "CPU.hpp"
#include "mainwindow.h"
#include <vector>
class CPU;
class ShortTermScheduler;
class LongTermScheduler;
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
void updateProcessTable(int index, Process p);
bool isFinished();
MainWindow * window;
void IOPreempt(Process p);
private:
kernel();
~kernel(){
}
pagetable * pTable;
int pidCounter = 0;
ShortTermScheduler * shortTerm;
LongTermScheduler * longTerm;
unsigned int pageSize; // size of each page
unsigned int longTermTimer; // time before long term runs
std::vector<Process > processTable;

};

#endif // KERNEL_H
