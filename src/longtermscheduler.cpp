#include "longtermscheduler.h"

// Uses priority queue to determine what process should be added into the ready queue

LongTermScheduler::LongTermScheduler()
{
    this->jobQueue = new PriorityQueue();
}

void LongTermScheduler::runScheduler(){
    if(CPU::getInstance().availableMemory() > 0 && this->jobQueue->getSize() > 0) {
        Process newProcess = this->jobQueue->removeProcess();
        this->jobQueue->ageProcesses(); // age the processes to reduce starvation
        kernel::getInstance().swapIn(newProcess); // put into the ready queue
    }
}

void LongTermScheduler::enqueueProcess(Process p){
    this->jobQueue->addProcess(p);
}
