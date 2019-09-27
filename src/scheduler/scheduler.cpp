#include "scheduler.hpp"
#include "../CPU/CPU.hpp"

Scheduler::Scheduler(int timeqc)
{
    cpu->setTimeQ(timeqc);
}

Scheduler::Scheduler()
{
    cpu->setTimeQ(20);
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

void Scheduler::round_robin()
{
    if (!(this->runningProcess))
    {
        this->timeQuantum = 0;
        this->runningProcess = this->readyQueue->dequeueProcess();
        this->runningProcess->setState(RUN);
    }
    this->timeQuantum++;
    if (cpu->getTimeQ() <= this->timeQuantum)
    {
        this->runningProcess->setState(READY);
        this->readyQueue->enqueueProcess(this->runningProcess);
        delete this->runningProcess;
    }
    else
    {
    }
}

void Scheduler::priority()
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
    switch (this->algorithmToUse)
    {
    case ROUND_ROBIN:
        this->round_robin();
    case PRIORITY_SCHEDULING:
        this->priority();
    default:
        break;
    }
}

void Scheduler::processWaitingQueue()
{
}
