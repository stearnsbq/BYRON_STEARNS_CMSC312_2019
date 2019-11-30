#include "shorttermscheduler.h"
#include "mainwindow.h"



ShortTermScheduler::ShortTermScheduler(ALGORITHM algoToUse, Core & parent) : parent(parent) {
    this->algorithmToUse = algoToUse;
    this->dp = new Dispatcher(parent);
}



void ShortTermScheduler::runScheduler(){
    switch (this->algorithmToUse)
    {
    case ROUND_ROBIN:
        this->roundRobin();
        break;
    case PRIORITY_SCHEDULING:
        //this->priority();
        break;
    case MULTILEVEL_FEEDBACK_QUEUE:
        this->feedBackQueue();
        break;
    default:
        break;
    }
    this->processWaitingQueue();
}

void ShortTermScheduler::enqueueProcess(Process p, QUEUE_TYPE q){
    switch (q) {
    case WAITING:
        this->waitingQueue.push(p);
        break;
    case MID:
        this->midLevel.push(p);
        break;
    case READY_Q:
        this->readyQueue.push(p);
        break;
    case BASE:
        this->readyQueue.push(p);
        break;
    }
}

void ShortTermScheduler::feedBackQueue(){
    if(!this->readyQueue.empty() || (parent.runningProcess.getLastQueue() == 0 && parent.runningProcess.getState() != EXIT) ) {
        this->roundRobinProcess(0, 8);
    }else if(!this->midLevel.empty() || (parent.runningProcess.getLastQueue() == 1 && parent.runningProcess.getState() != EXIT)) {
        this->roundRobinProcess(1, 16);
    }else if (!this->baseLevel.empty()|| (parent.runningProcess.getLastQueue() == 2 && parent.runningProcess.getState() != EXIT)) {
        this->roundRobinProcess(2, 20);
    }
}


void ShortTermScheduler::roundRobinProcess(int queue, int timeQ){
    std::queue<Process> * queueToProcess = nullptr;
    switch (queue) {
    case 0:
        queueToProcess = &this->readyQueue;
        break;
    case 1:
        queueToProcess = &this->midLevel;
        break;
    case 2:
        queueToProcess = &this->baseLevel;
        break;
    }

    if(queueToProcess != nullptr) {

        if(parent.runningProcess.getState() == EXIT && !queueToProcess->empty()) {
            this->timeQuantum = 0;
            Process newProcess = queueToProcess->front();
            queueToProcess->pop();
            newProcess.setState(RUN);
            parent.runningProcess = newProcess;
            kernel::getInstance().updateProcessTable(  newProcess);
        }

        if(this->timeQuantum >= timeQ) {
            parent.runningProcess.setLastQueue(queue >= 2 ? 2 : queue +1);
            Process rotate = parent.runningProcess;
            rotate.setState(READY);
            parent.runningProcess.setState(EXIT);
            kernel::getInstance().updateProcessTable(  rotate);
            switch (queue) {
            case 0:
                emit kernel::getInstance().window->print("PID " + std::to_string(rotate.getPid()) +  " demoting from q1 -> q2");
                this->midLevel.push(rotate);
                break;
            case 1:
                emit kernel::getInstance().window->print(  "PID " + std::to_string(rotate.getPid()) +" demoting from q2 -> q3");
                this->baseLevel.push(rotate);
                break;
            case 2:
                emit kernel::getInstance().window->print(  "PID " + std::to_string(rotate.getPid()) +" preempt to back");
                this->baseLevel.push(rotate);
                break;
            }

        }


    }
    this->timeQuantum++;
}



void ShortTermScheduler::roundRobin()
{
    if (parent.runningProcess.getState() == EXIT && !this->readyQueue.empty())
    {
        this->timeQuantum = 0;
        Process newProcess = this->readyQueue.front();
        this->readyQueue.pop();
        newProcess.setState(RUN);
        CPU::getInstance().setRunningProcess(newProcess);
        kernel::getInstance().updateProcessTable(  newProcess);
    }

    if (this->timeQuantum >= 20) // ran out of time for this process preempt it out
    {
        Process rotate = parent.runningProcess;
        parent.runningProcess.setState(EXIT);
        rotate.setState(READY);
        this->readyQueue.push(rotate);
        emit kernel::getInstance().window->print("preempt");
        kernel::getInstance().updateProcessTable(  rotate);
        this->timeQuantum = 0;
    }else{
        if (parent.runningProcess.getCurrentBurst() > 0) // if instruction is not done run it
        {
            CPU::getInstance().executeInstruction(20);
        }
        else if (parent.runningProcess.getInstructions().size() - 1 > parent.runningProcess.getProgramCounter())// if instruction is done increment PC
        {
            std::string out = "PC " + std::to_string(parent.runningProcess.getProgramCounter()) + " instr: " + parent.runningProcess.getCurrentInstruction().getInstr();
            std::cout << out << std::endl;
            emit kernel::getInstance().window->print(out);
            parent.runningProcess.incrementPC();
        }else{ // process is done exit
            Process rotate = parent.runningProcess;
            rotate.setState(EXIT);
            kernel::getInstance().updateProcessTable(  rotate);
            parent.runningProcess.setState(EXIT);
        }

    }

    this->timeQuantum++;
}


void ShortTermScheduler::processWaitingQueue()
{
    if(!this->waitingQueue.empty()) {
        if(this->waitingQueue.front().getCurrentBurst() > 0) {
            //  emit kernel::getInstance().window->print("WAITING BURST: " + std::to_string(this->waitingQueue->peek()->getCurrentBurst()) + " PC: " + std::to_string(this->waitingQueue->peek()->getPid()) + " IO: " + this->waitingQueue->peek()->getCurrentInstruction().getInstr());
            //  std::cout << "WAITING BURST: " + std::to_string(this->waitingQueue->peek()->getCurrentBurst()) + " PC: " + std::to_string(this->waitingQueue->peek()->getPid()) + " IO: " + this->waitingQueue->peek()->getCurrentInstruction().getInstr() << std::endl;
            this->waitingQueue.front().decrementBurst();
        }else{
            Process rotate = this->waitingQueue.front();
            this->waitingQueue.pop();
            emit kernel::getInstance().window->print("WAITING DONE PID: " + std::to_string(rotate.getPid()));
            // std::cout << "WAITING DONE PID: " + std::to_string(rotate.getPid()) << std::endl;
            rotate.setState(READY);
            rotate.incrementPC();
            if(this->algorithmToUse == MULTILEVEL_FEEDBACK_QUEUE) {
                switch (rotate.getLastQueue()) {
                case 0:
                    this->readyQueue.push(rotate);
                    break;
                case 1:
                    this->midLevel.push(rotate);
                    break;
                case 2:
                    this->baseLevel.push(rotate);
                    break;
                }
            }else{
                this->readyQueue.push(rotate);
            }
            CPU::getInstance().mutexLock->unlock();
        }
    }
}
