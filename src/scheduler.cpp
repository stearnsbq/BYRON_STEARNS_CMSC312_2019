#include "scheduler.hpp"
#include "CPU.hpp"
#include <QMessageBox>
int gPid;
MainWindow * m;

Scheduler::Scheduler(ALGORITHM algorithm)
{
    this->timeQuantum = 0;
    this->isRunning = false;
    gPid = 0;
    if(algorithm == MULTILEVEL_FEEDBACK_QUEUE){
        this->topLevel = new Queue();  // time quan of 8
        this->midLevel = new Queue(); // time quan of 16
        this->baseLevel = new Queue(); // RR with time quan of 20
    }else{
        this->readyQueue = new Queue();
    }
    this->newQueue = new Queue();
    this->waitingQueue = new Queue();
    this->runningProcess.setState(EXIT);
    this->algorithmToUse = algorithm;
    cpu = new CPU();
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

void Scheduler::clock(int time, QString unit){
    while(this->isRunning){
      run();
      if(unit == "ms"){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
      }else if(unit == "ns"){
          std::this_thread::sleep_for(std::chrono::nanoseconds(time));
      }else{
          std::this_thread::sleep_for(std::chrono::seconds(time));
      }




    }
    this->timeQuantum = 0;
    this->totalProcesses = 0;
}

void Scheduler::start(MainWindow * window, int time, QString unit)
{

    if(!this->isRunning && !this->newQueue->isEmpty()){
        this->isRunning = true;
        this->timeQuantum = 0;
        m = window;
        this->clockThread = std::thread(&Scheduler::clock, this, time, unit);
        this->clockThread.join();
        emit m->print("Done!");
        emit m->done();
        this->totalProcesses = 0;
    }else{
        emit window->done();
        emit window->print("No processes loaded!!");
    }
}

void Scheduler::run()
{
    this->processNewQueue();
    this->processReadyQueue();
    this->processWaitingQueue();
}

void Scheduler::round_robin()
{
    if (this->runningProcess.getState() == EXIT && !this->readyQueue->isEmpty())
    {
        this->timeQuantum = 0;
        this->runningProcess = this->readyQueue->dequeueProcess();
        this->runningProcess.setState(RUN);
    }else if(this->runningProcess.getState() == EXIT && this->waitingQueue->isEmpty() && this->readyQueue->isEmpty()){
        this->isRunning = false;
        return;
    }

    if (this->timeQuantum >= 20) // ran out of time for this process preempt it out
    {
        emit m->print("preempt out!");
        Process rotate = this->runningProcess;
        this->runningProcess.setState(EXIT);
        rotate.setState(READY);
        this->readyQueue->enqueueProcess(rotate);
    }else{
        if (this->runningProcess.getCurrentBurst() > 0) // if instruction is not done run it
        {
            if(this->runningProcess.getCurrentInstruction().getType() == OUT){
                emit m->print(this->runningProcess.getCurrentInstruction().getOut());
            }else if(this->runningProcess.getCurrentInstruction().getType() == IO){
              // emit m->print("IO, PREEMPT INTO WAITING QUEUE: DEBUG: PC " + std::to_string(this->runningProcess.getProgramCounter()) + " DEBUG: " + std::to_string(this->runningProcess.getPid()) + " DEBUG STUFF: " + std::to_string(this->runningProcess.getState() == EXIT && this->waitingQueue->isEmpty() && this->readyQueue->isEmpty()) + " DEBUG: " + std::to_string(this->runningProcess.getCurrentBurst() ));
                Process rotate = this->runningProcess;
                rotate.setState(WAIT);
                this->runningProcess.setState(EXIT);
                this->waitingQueue->enqueueProcess(rotate);
           }else{

                std::string str = "RUNNING!! PID: " + std::to_string(this->runningProcess.getPid()) + " " + this->runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(this->runningProcess.getCurrentBurst());
                emit m->print(str);
                this->runningProcess.decrementBurst();
            }
        }
        else if (this->runningProcess.getInstructions().size() - 1 > this->runningProcess.getProgramCounter()) // if instruction is done increment PC
        {
            std::string out =   "PC " + std::to_string(this->runningProcess.getProgramCounter()) + " instr: " + this->runningProcess.getCurrentInstruction().getInstr();
            emit m->print(out);
            this->runningProcess.incrementPC();
        }else{ // process is done exit
            this->runningProcess.setState(EXIT);
            cpu->freeMemory(this->runningProcess.getMemoryBlock());
            this->runningProcess.setCycles(-1);
            this->processesRan++;
        }
        }

        this->timeQuantum++;
}

void Scheduler::priority()
{

}



void Scheduler::roundRobinProcess(int queueNum, int timeQ){
    Queue * queueToProcess = nullptr;
    switch (queueNum) {
     case 0:
        queueToProcess = this->topLevel;
        break;
     case 1:
        queueToProcess = this->midLevel;
        break;
     case 2:
        queueToProcess = this->baseLevel;
        break;
    }

    if(queueToProcess != nullptr){

      if(this->runningProcess.getState() == EXIT && !queueToProcess->isEmpty()){
            this->timeQuantum = 0;
            this->runningProcess = queueToProcess->dequeueProcess();
            this->runningProcess.setLastQueue(queueNum);
            this->runningProcess.setState(RUN);
      }else if(this->runningProcess.getState() == EXIT && this->topLevel->isEmpty() && this->midLevel->isEmpty() && this->baseLevel->isEmpty() && this->waitingQueue->isEmpty()){
          this->isRunning = false;
          return;
      }

      if(this->timeQuantum >= timeQ){

          Process rotate = this->runningProcess;
          rotate.setState(READY);
          this->runningProcess.setState(EXIT);
          switch (queueNum) {
           case 0:
              emit m->print("Process q1 -> q2");
              this->midLevel->enqueueProcess(rotate);
              break;
           case 1:
              emit m->print("Process q2 -> q3");
              this->baseLevel->enqueueProcess(rotate);
              break;
           case 2:
              emit m->print("preempt to back");
              this->baseLevel->enqueueProcess(rotate);
              break;
          }

      }else{
          if(this->runningProcess.getCurrentBurst() > 0){
              if(this->runningProcess.getCurrentInstruction().getType() == OUT){
                  emit m->print(this->runningProcess.getCurrentInstruction().getOut());
              }else if(this->runningProcess.getCurrentInstruction().getType() == IO){
                  emit m->print("IO, PREEMPT INTO WAITING QUEUE");
                  Process rotate = this->runningProcess;
                  rotate.setState(WAIT);
                  this->runningProcess.setState(EXIT);
                  this->waitingQueue->enqueueProcess(rotate);
              }else{
                  std::string str = "RUNNING!! PID: " + std::to_string(this->runningProcess.getPid()) + " " + this->runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(this->runningProcess.getCurrentBurst());
                  emit m->print(str);
                  this->runningProcess.decrementBurst();
              }
          }else if(this->runningProcess.getInstructions().size() - 1 > this->runningProcess.getProgramCounter()){
                this->runningProcess.incrementPC();
          }else{
              this->runningProcess.setState(EXIT);
              cpu->freeMemory(this->runningProcess.getMemoryBlock());
          }

      }
    }
this->timeQuantum++;
}




void Scheduler::feedBackQueue(){
    if(!this->topLevel->isEmpty()){
        this->roundRobinProcess(0, 8);
    }else if(!this->midLevel->isEmpty()){
        this->roundRobinProcess(1, 16);
    }else{
         this->roundRobinProcess(2, 20);
    }
}

void Scheduler::processNewQueue()
{
    if (!this->newQueue->isEmpty())
    {
        if (cpu->availableMemory() >= this->newQueue->peek()->getMemoryReq())
       {
            Process process = this->newQueue->dequeueProcess();
            process.setMemoryBlock(cpu->allocateMemory(process.getMemoryReq()));
            process.setState(READY);
            if(this->algorithmToUse == MULTILEVEL_FEEDBACK_QUEUE){
                this->topLevel->enqueueProcess(process);
            }else{
                this->readyQueue->enqueueProcess(process);
            }
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
    case MULTILEVEL_FEEDBACK_QUEUE:
        this->feedBackQueue();
        break;
    default:
        break;
    }
}

void Scheduler::processWaitingQueue()
{
    if(!this->waitingQueue->isEmpty()){
        if(this->waitingQueue->peek()->getCurrentBurst() > 0){
             emit m->print("WAITING BURST: " + std::to_string(this->waitingQueue->peek()->getCurrentBurst()) + " PC: " + std::to_string(this->waitingQueue->peek()->getPid()) + " IO: " + this->waitingQueue->peek()->getCurrentInstruction().getInstr());
            this->waitingQueue->peek()->decrementBurst();
        }else{
            Process rotate = this->waitingQueue->dequeueProcess();
             emit m->print("WAITING DONE: " + std::to_string(rotate.getPid()));
            rotate.setState(READY);
            rotate.incrementPC();
            if(this->algorithmToUse == MULTILEVEL_FEEDBACK_QUEUE){
                switch (rotate.getLastQueue()) {
                case 0:
                    this->topLevel->enqueueProcess(rotate);
                    break;
                case 1:
                    this->midLevel->enqueueProcess(rotate);
                    break;
                case 2:
                    this->baseLevel->enqueueProcess(rotate);
                    break;
                }
            }else{
                this->readyQueue->enqueueProcess(rotate);
            }
        }
    }
}
