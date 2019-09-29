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
    this->isRunning = false;
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
    this->totalProcesses++;
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
    while(this->isRunning){
       run();
       //std::cout << "cpu tick" << std::endl;
     // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Scheduler::start()
{
    this->isRunning = true;
    this->clockThread = std::thread(&Scheduler::clock, this);
}

void Scheduler::run()
{
    this->processNewQueue();
    this->processReadyQueue();
    this->processWaitingQueue();
}

void Scheduler::round_robin()
{

    if (this->runningProcess.getCycles() == -1 && !this->readyQueue->isEmpty())
    {
        this->timeQuantum = 0;
        this->runningProcess = this->readyQueue->dequeueProcess();
        this->runningProcess.setState(RUN);
    }else if(this->processesRan == this->totalProcesses){
    this->isRunning = false;
       // system("cls");
        std::cout << "Processes done running!" << std::endl;
    }

    if (this->timeQuantum >= 20) // ran out of time for this process preempt it out
    {
        std::cout << "preempt out!!" << std::endl;
        Process rotate = this->runningProcess;
        this->runningProcess.setCycles(-1);
        rotate.setState(READY);
        this->readyQueue->enqueueProcess(rotate);
    }
    else if(this->runningProcess.getCurrentInstruction().getType() == IO){
        std::cout << "WAITING PREEMPT" << std::endl;
        Process rotate = this->runningProcess;
        this->runningProcess.setCycles(-1);
        rotate.setState(WAIT);
        this->waitingQueue->enqueueProcess(rotate);
    }
    else{
       
        if (this->runningProcess.getCurrentBurst() >= 0) // if instruction is not done run it
        {
            std::cout << "RUNNING!! PID: " << this->runningProcess.getPid() << " " << this->runningProcess.getCurrentInstruction().getInstr() << " burst #" << this->runningProcess.getCurrentBurst() << std::endl;
            this->runningProcess.decrementBurst();
        }
        else if (this->runningProcess.getInstructions().size() - 1 > this->runningProcess.getProgramCounter()) // if instruction is done increment PC
        {
            std::cout << "PC " << this->runningProcess.getInstructions().size() << " " << this->runningProcess.getProgramCounter() << std::endl;
            this->runningProcess.incrementPC(); // instruction is finished increment the PC
        }else{ // process is done exit
            this->runningProcess.setState(EXIT);
            this->processesRan++;
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

        if (cpu->availableMemory() >= this->newQueue->peek()->getMemoryReq())
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
    if(!this->waitingQueue->isEmpty()){
        if(this->waitingQueue->peek()->getCurrentBurst() > 0){
            this->waitingQueue->peek()->decrementBurst();
        }else{
            Process rotate = this->waitingQueue->dequeueProcess();
            rotate.setState(READY);
            rotate.incrementPC();
            this->readyQueue->enqueueProcess(rotate);
        }
    }
}
