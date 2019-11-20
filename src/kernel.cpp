#include "kernel.h"


kernel::kernel()
{
    // this->longTerm = new LongTermScheduler();
    //  this->shortTerm = new ShortTermScheduler();
    this->jobPool = new PriorityQueue();
    this->longTermTimer = 0;
}

void kernel::schedule(){
    if(longTermTimer <= 0) {
        //   this->longTerm->runScheduler();
        this->longTermTimer = 10;
    }
    // this->shortTerm->runScheduler();
    this->longTermTimer--;
}


void kernel::updateProcessTable(int index, Process p){
    this->processTable[index] = p;
    emit window->updateProcessListGUI();
}

void kernel::newProcess(Process& p){
    p.setState(NEW);
    p.setPid(pidCounter++);
    this->jobPool->addProcess(p);
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

Process kernel::getNextProcessInPool(){
    std::lock_guard<std::mutex>(this->jobPoolMutex);
    if(!this->jobPool->isEmpty()) {
        return this->jobPool->removeProcess();
    }
}

bool kernel::isJobPoolEmpty(){
    return this->jobPool->isEmpty();
}

void kernel::swapIn(Process p){
    std::vector<page> pages = CPU::getInstance().alloc(p.getMemoryReq());
    p.pages = pages;
    if(!pages.empty()) {
        //  this->shortTerm->enqueueProcess(p, READY_Q);
    }
}

void kernel::IOPreempt(Process p){
    // this->shortTerm->enqueueProcess(p, WAITING);
}


std::vector<Process> kernel::getListOfProcesses(){
    return this->processTable;
}


