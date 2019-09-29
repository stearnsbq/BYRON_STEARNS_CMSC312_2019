#include "scheduler.hpp"
#include "CPU.hpp"

 int gPid;


Scheduler::Scheduler(int timeqc)
{
    this->newQueue = new Queue();
    this->readyQueue = new Queue();
    this->waitingQueue = new Queue();
    this->timeQuantum = 0;
    this->runningProcess.setCycles(-1);
    cpu = new CPU();
    cpu->setTimeQ(timeqc);
}

Scheduler::Scheduler()
{

    this->newQueue = new Queue();
    this->readyQueue = new Queue();
    this->waitingQueue = new Queue();
    this->algorithmToUse = ROUND_ROBIN;
    this->runningProcess.setCycles(-1);
    this->timeQuantum = 0;
    cpu = new CPU();
    gPid = 0;
    cpu->setTimeQ(20);
}

Scheduler::~Scheduler()
{
    delete this->newQueue;
    delete this->waitingQueue;
    delete this->readyQueue;
}

void Scheduler::addNewProcess(Process process)
{
    process.setPid(gPid++);
    this->newQueue->enqueueProcess(process);
}

void Scheduler::addReadyProcess(Process Process)
{
    this->readyQueue->enqueueProcess(Process);
}

Process Scheduler::getNextReadyProcess()
{
    return this->readyQueue->dequeueProcess();
}

void Scheduler::rotateProcess()
{
}

void Scheduler::clock(){
    while(1){
       run();
       std::cout << "cpu tick" << std::endl;
     // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Scheduler::start()
{
    this->clockThread = std::thread(&Scheduler::clock, this);
}

void Scheduler::run()
{
    this->processNewQueue();
    this->processReadyQueue();
    // this->processWaitingQueue();
}

void Scheduler::round_robin()
{



    if (this->runningProcess.getCycles() == -1)
    {
        this->timeQuantum = 0;
        this->runningProcess = this->readyQueue->dequeueProcess();
        this->runningProcess.setState(RUN);
        //this->runningProcess.setCycles(-1);
    }

    if (this->timeQuantum >= 20) // ran out of time for this process rotate it out
    {
        std::cout << "switch out!!" << std::endl;
        Process rotate = this->runningProcess;
        this->runningProcess.setCycles(-1);
        rotate.setState(READY);
        this->readyQueue->enqueueProcess(rotate);
    }
    else
    {
       
        if (this->runningProcess.getCurrentBurst() > 0) // if instruction is not done run it
        {
            std::cout << "RUNNING!! PID: " << this->runningProcess.getPid() << " " << this->runningProcess.getCurrentInstruction().getInstr() << " burst #" << this->runningProcess.getCurrentBurst() << std::endl;
            this->runningProcess.decrementBurst();
        }
        else if (this->runningProcess.getInstructions().size() > this->runningProcess.getProgramCounter())
        {
            std::cout << "PC" << std::endl;
            this->runningProcess.incrementPC(); // instruction is finished increment the PC
        }
        this->timeQuantum++;
    }
}

void Scheduler::priority()
{
}

void Scheduler::processNewQueue()
{
    if (!this->newQueue->isEmpty())
    {

        if (cpu->availableMemory() >= this->newQueue->peek().getMemoryReq())
        {

            Process process = this->newQueue->dequeueProcess();

            cpu->allocateMemory(process.getMemoryReq());
            process.setState(READY);
            this->readyQueue->enqueueProcess(process);
        }
    }
}

void Scheduler::processReadyQueue()
{

    switch (this->algorithmToUse)
    {
    case ROUND_ROBIN:
        this->round_robin();
        break;
    case PRIORITY_SCHEDULING:
        this->priority();
        break;
    default:
        break;
    }
}

void Scheduler::processWaitingQueue()
{
}
