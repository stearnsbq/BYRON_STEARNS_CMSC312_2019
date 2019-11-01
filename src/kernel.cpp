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
    this->window->print("Long term scheduler running in: " + std::to_string(this->longTermTimer));
    if(longTermTimer <= 0) {
        this->longTerm->runScheduler();
        this->longTermTimer = 10;
    }
    this->shortTerm->runScheduler();
    this->longTermTimer--;
}

void kernel::updateProcessTable(int index, Process p){
    this->processTable[index] = p;
}

void kernel::newProcess(Process& p){
    p.setState(NEW);
    p.setPid(pidCounter++);
    this->longTerm->enqueueProcess(p);
    this->processTable.push_back(p);
}

bool kernel::isFinished(){
    for(int i = 0; i < this->processTable.size(); i++) {
        if(this->processTable[i].getState() != EXIT) {
            return false;
        }
    }
    return true;
}

void kernel::swapIn(Process p){
    this->shortTerm->enqueueProcess(p);
}


