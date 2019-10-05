#include "scheduler.hpp"
#include "CPU.hpp"
int gPid;
MainWindow * m;

Scheduler::Scheduler(int timeqc)
{
    this->processesRan = 0;
    this->totalProcesses = 0;
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
    this->processesRan = 0;
    this->totalProcesses = 0;
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

void Scheduler::clock(int time, QString unit){
    while(this->isRunning){
      run();
      if(unit == "ms"){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
      }else{
          std::this_thread::sleep_for(std::chrono::seconds(time));
      }

    }
}

void Scheduler::start(MainWindow * window, int time, QString unit)
{
    this->isRunning = true;
    this->processesRan = 0;
    this->timeQuantum = 0;
    m = window;
    this->clockThread = std::thread(&Scheduler::clock, this, time, unit);
    this->clockThread.join();
    emit m->print("Done!");
    emit m->done();
    this->totalProcesses = 0;
}

void Scheduler::run()
{
    this->processNewQueue();
    this->processReadyQueue();
    this->processWaitingQueue();
}

void Scheduler::round_robin()
{
    if (this->runningProcess.getCycles() == -1 || this->runningProcess.getState() == WAIT && !this->readyQueue->isEmpty())
    {
        this->timeQuantum = 0;
        this->runningProcess = this->readyQueue->dequeueProcess();
        this->runningProcess.setState(RUN);
    }else if(this->processesRan == this->totalProcesses){
        this->isRunning = false;
        this->runningProcess.setCycles(-1);
        return;
    }

   if(this->runningProcess.getState() != WAIT){

    if (this->timeQuantum >= 20) // ran out of time for this process preempt it out
    {
        emit m->print("preempt out!");
        Process rotate = this->runningProcess;
        this->runningProcess.setCycles(-1);
        rotate.setState(READY);
        this->readyQueue->enqueueProcess(rotate);
    }
    else if(this->runningProcess.getCurrentInstruction().getType() == IO){

         emit m->print("WAITING PREEMPT");
        this->runningProcess.setState(WAIT);
        this->waitingQueue->enqueueProcess(this->runningProcess);
    }else{

        if (this->runningProcess.getCurrentBurst() > 0) // if instruction is not done run it
        {
            if(this->runningProcess.getCurrentInstruction().getType() == OUT){
                emit m->print(this->runningProcess.getCurrentInstruction().getOut());
            }
            std::string str = "RUNNING!! PID: " + std::to_string(this->runningProcess.getPid()) + " " + this->runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(this->runningProcess.getCurrentBurst());

            emit m->print(str);
            this->runningProcess.decrementBurst();
        }
        else if (this->runningProcess.getInstructions().size() - 1 > this->runningProcess.getProgramCounter()) // if instruction is done increment PC
        {
            std::string out =   "PC " + std::to_string(this->runningProcess.getProgramCounter()) + " instr: " + this->runningProcess.getCurrentInstruction().getInstr();
            emit m->print(out);
            this->runningProcess.incrementPC(); // instruction is finished increment the PC
        }else{ // process is done exit
            this->runningProcess.setState(EXIT);
            cpu->freeMemory(this->runningProcess.getMemoryBlock());
            this->processesRan++;
        }
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
          //  emit m->updateMemoryGraphic(cpu->getMemor);
            process.setMemoryBlock(cpu->allocateMemory(process.getMemoryReq()));
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
           // std::cout << "WAITING DONE" << std::endl;
             emit m->print("WAITING DONE");
            Process rotate = this->waitingQueue->dequeueProcess();
            rotate.setState(READY);
            rotate.incrementPC();
            this->readyQueue->enqueueProcess(rotate);
        }
    }
}
