#include "longtermscheduler.h"
#include "kernel.h"
#include "CPU.hpp"

// Uses priority queue to determine what process should be added into the ready queue

LongTermScheduler::LongTermScheduler(ShortTermScheduler * sched, int coreNum)
{
    this->scheduler = sched;
    this->coreNum = coreNum;
}
LongTermScheduler::~LongTermScheduler(){

}

void LongTermScheduler::runScheduler(){

    if(CPU::getInstance().availableMemory() > 0 && !kernel::getInstance().isJobPoolEmpty()) {

        Process p = kernel::getInstance().getNextProcessInPool();

        if(p.getPriority() >= 0) {
            p.setState(READY);
            kernel::getInstance().updateProcessTable(p);
            p.pages = CPU::getInstance().alloc(p.getMemoryReq());
            this->scheduler->enqueueProcess(p, READY_Q);
            kernel::getInstance().window->updateSchedulerUI(p, "remove");
        }

    }

}


