#include "scheduler.hpp"
#include "../CPU/CPU.hpp"

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
    delete this->newQueue;
    delete this->readyQueue;
}

void Scheduler::addNewProcess(Process *Process)
{
    this->newQueue->enqueueProcess(Process);
}

void Scheduler::addReadyProcess(Process *Process)
{
    this->readyQueue->enqueueProcess(Process);
}

Process *Scheduler::getNextReadyProcess()
{
    return this->readyQueue->dequeueProcess();
}

void Scheduler::rotateProcess()
{
}

void Scheduler::processNewQueue()
{
    if (!this->newQueue->isEmpty())
    {

        if (cpu->availableMemory() >= this->newQueue->peek()->getMemoryReq())
        {
            Process *process = this->newQueue->dequeueProcess();
            cpu->allocateMemory(process->getMemoryReq());
            process->setState(READY);
            this->readyQueue->enqueueProcess(process);
        }
    }
    else
    {
        throw "Empty Queue!";
    }
}

void Scheduler::processReadyQueue()
{
}

void Scheduler::processWaitingQueue()
{
}
