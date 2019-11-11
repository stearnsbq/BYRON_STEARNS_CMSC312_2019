#include "kernel.h"
class CPU;
class LongTermScheduler;
class ShortTermScheduler;

kernel::kernel()
{
    this->longTerm = new LongTermScheduler();
    this->shortTerm = new ShortTermScheduler();
    this->longTermTimer = 0;
}

void kernel::schedule(){
    if(longTermTimer <= 0) {
        this->longTerm->runScheduler();
        this->longTermTimer = 10;
    }
    this->shortTerm->runScheduler();
    this->longTermTimer--;
}


void kernel::updateProcessTable(int index, Process p){
    this->processTable[index] = p;
    emit window->updateProcessListGUI();
}

void kernel::newProcess(Process& p){
    p.setState(NEW);
    p.setPid(pidCounter++);
    this->longTerm->enqueueProcess(p);
    this->processTable.push_back(p);
    emit window->updateProcessListGUI();
}

bool kernel::isFinished(){
    for(int i = 0; i < this->processTable.size(); i++) {
        if(this->processTable[i].getState() != EXIT || this->processTable[i].getCurrentBurst() > 0) {
            return false;
        }
    }
    return true;
}

void kernel::swapIn(Process p){
    std::vector<page> pages = CPU::getInstance().alloc(p.getMemoryReq());
    p.pages = pages;
    if(!pages.empty()) {
        this->shortTerm->enqueueProcess(p, READY_Q);
    }
}

void kernel::IOPreempt(Process p){
    this->shortTerm->enqueueProcess(p, WAITING);
}


std::vector<Process > kernel::getListOfProcesses(){
    return this->processTable;
}


