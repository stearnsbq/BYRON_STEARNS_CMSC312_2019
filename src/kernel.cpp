#include "kernel.h"


kernel::kernel()
{
    this->longTermTimer = 0;
    this->shutDown = false;
}

void kernel::schedule(){
    if(longTermTimer <= 0) {
        //   this->longTerm->runScheduler();
        this->longTermTimer = 10;
    }
    // this->shortTerm->runScheduler();
    this->longTermTimer--;
}


void kernel::updateProcessTable(Process p){
    this->processTable[p.getPid()] = p;
    emit window->updateProcessListGUI();
}

void kernel::newProcess(Process& p){
    p.setState(NEW);
    p.setPid(pidCounter++);
    this->jobPool.push(p);
    this->processTable.push_back(p);
    emit window->updateProcessListGUI();
}


bool kernel::compare( Process& p1,  Process& p2){
    return p1.getPriority() < p2.getPriority();
}




bool kernel::isFinished(){
    return this->shutDown;
}

Process kernel::getNextProcessInPool(){
    std::lock_guard<std::mutex> lock{this->jobPoolMutex};
    if(!this->jobPool.empty()) {
        try {

            Process p = this->jobPool.top();
            this->jobPool.pop();
            return p;
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
    return Process();
}

bool kernel::isJobPoolEmpty(){
    return this->jobPool.empty();
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


