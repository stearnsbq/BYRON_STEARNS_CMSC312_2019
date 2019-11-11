#include "shorttermscheduler.h"
#include "mainwindow.h"


ShortTermScheduler::ShortTermScheduler() : ShortTermScheduler(MULTILEVEL_FEEDBACK_QUEUE)
{

}

ShortTermScheduler::ShortTermScheduler(ALGORITHM algoToUse)
{
    this->algorithmToUse = algoToUse;
    this->readyQueue = new Queue();
    this->midLevel = new Queue();
    this->baseLevel = new Queue();
    this->waitingQueue = new Queue();
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
        this->waitingQueue->enqueueProcess(p);
        break;
    case MID:
        this->midLevel->enqueueProcess(p);
        break;
    case READY_Q:
        this->readyQueue->enqueueProcess(p);
        break;
    case BASE:
        this->readyQueue->enqueueProcess(p);
        break;
    }
}

void ShortTermScheduler::feedBackQueue(){
    if(!this->readyQueue->isEmpty() || (CPU::getInstance().getRunningProcess().getLastQueue() == 0 && CPU::getInstance().getRunningProcess().getState() != EXIT) ) {
        this->roundRobinProcess(0, 8);
    }else if(!this->midLevel->isEmpty() || (CPU::getInstance().getRunningProcess().getLastQueue() == 1 && CPU::getInstance().getRunningProcess().getState() != EXIT)) {
        this->roundRobinProcess(1, 16);
    }else if (!this->baseLevel->isEmpty() || (CPU::getInstance().getRunningProcess().getLastQueue() == 2 && CPU::getInstance().getRunningProcess().getState() != EXIT)) {
        this->roundRobinProcess(2, 20);
    }
}


void ShortTermScheduler::roundRobinProcess(int queue, int timeQ){
    Queue * queueToProcess = nullptr;
    switch (queue) {
    case 0:
        queueToProcess = this->readyQueue;
        break;
    case 1:
        queueToProcess = this->midLevel;
        break;
    case 2:
        queueToProcess = this->baseLevel;
        break;
    }

    if(queueToProcess != nullptr) {

        if(CPU::getInstance().getRunningProcess().getState() == EXIT && !queueToProcess->isEmpty()) {
            this->timeQuantum = 0;
            Process newProcess = queueToProcess->dequeueProcess();
            newProcess.setState(RUN);
            CPU::getInstance().setRunningProcess(newProcess);
            kernel::getInstance().updateProcessTable(newProcess.getPid(),  newProcess);
        }

        if(this->timeQuantum >= timeQ) {
            CPU::getInstance().getRunningProcess().setLastQueue(queue >= 2 ? 2 : queue +1);
            Process rotate = CPU::getInstance().getRunningProcess();
            rotate.setState(READY);
            CPU::getInstance().getRunningProcess().setState(EXIT);
            kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);
            switch (queue) {
            case 0:
                emit kernel::getInstance().window->print("PID " + std::to_string(rotate.getPid()) +  " demoting from q1 -> q2");
                this->midLevel->enqueueProcess(rotate);
                break;
            case 1:
                emit kernel::getInstance().window->print(  "PID " + std::to_string(rotate.getPid()) +" demoting from q2 -> q3");
                this->baseLevel->enqueueProcess(rotate);
                break;
            case 2:
                emit kernel::getInstance().window->print(  "PID " + std::to_string(rotate.getPid()) +" preempt to back");
                this->baseLevel->enqueueProcess(rotate);
                break;
            }

        }else{
            if(CPU::getInstance().getRunningProcess().getCurrentBurst() > 0) {

                CPU::getInstance().executeInstruction(timeQ);

            }else if(CPU::getInstance().getRunningProcess().getInstructions().size() - 1 > CPU::getInstance().getRunningProcess().getProgramCounter()) {
                std::string out = "PC " + std::to_string(CPU::getInstance().getRunningProcess().getProgramCounter()) + " instr: " + CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr();
                std::cout << out << std::endl;
                emit kernel::getInstance().window->print(out);
                CPU::getInstance().getRunningProcess().incrementPC();
            }else{
                Process rotate = CPU::getInstance().getRunningProcess();
                rotate.setState(EXIT);
                kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);
                CPU::getInstance().free(rotate.pages);
                CPU::getInstance().getRunningProcess().setState(EXIT);
            }
        }
    }
    this->timeQuantum++;
}



void ShortTermScheduler::roundRobin()
{
    if (CPU::getInstance().getRunningProcess().getState() == EXIT && !this->readyQueue->isEmpty())
    {
        this->timeQuantum = 0;
        Process newProcess = this->readyQueue->dequeueProcess();
        newProcess.setState(RUN);
        CPU::getInstance().setRunningProcess(newProcess);
        kernel::getInstance().updateProcessTable(newProcess.getPid(),  newProcess);
    }

    if (this->timeQuantum >= 20) // ran out of time for this process preempt it out
    {
        Process rotate = CPU::getInstance().getRunningProcess();
        CPU::getInstance().getRunningProcess().setState(EXIT);
        rotate.setState(READY);
        this->readyQueue->enqueueProcess(rotate);
        emit kernel::getInstance().window->print("preempt");
        kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);
        this->timeQuantum = 0;
    }else{
        if (CPU::getInstance().getRunningProcess().getCurrentBurst() > 0) // if instruction is not done run it
        {
            CPU::getInstance().executeInstruction(20);
        }
        else if (CPU::getInstance().getRunningProcess().getInstructions().size() - 1 > CPU::getInstance().getRunningProcess().getProgramCounter())// if instruction is done increment PC
        {
            std::string out = "PC " + std::to_string(CPU::getInstance().getRunningProcess().getProgramCounter()) + " instr: " + CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr();
            std::cout << out << std::endl;
            emit kernel::getInstance().window->print(out);
            CPU::getInstance().getRunningProcess().incrementPC();
        }else{ // process is done exit
            Process rotate = CPU::getInstance().getRunningProcess();
            rotate.setState(EXIT);
            kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);
            CPU::getInstance().getRunningProcess().setState(EXIT);
        }

    }

    this->timeQuantum++;
}


void ShortTermScheduler::processWaitingQueue()
{
    if(!this->waitingQueue->isEmpty()) {
        if(this->waitingQueue->peek()->getCurrentBurst() > 0) {
            //  emit kernel::getInstance().window->print("WAITING BURST: " + std::to_string(this->waitingQueue->peek()->getCurrentBurst()) + " PC: " + std::to_string(this->waitingQueue->peek()->getPid()) + " IO: " + this->waitingQueue->peek()->getCurrentInstruction().getInstr());
            std::cout << "WAITING BURST: " + std::to_string(this->waitingQueue->peek()->getCurrentBurst()) + " PC: " + std::to_string(this->waitingQueue->peek()->getPid()) + " IO: " + this->waitingQueue->peek()->getCurrentInstruction().getInstr() << std::endl;
            this->waitingQueue->peek()->decrementBurst();
        }else{
            Process rotate = this->waitingQueue->dequeueProcess();
            emit kernel::getInstance().window->print("WAITING DONE PID: " + std::to_string(rotate.getPid()));
            std::cout << "WAITING DONE PID: " + std::to_string(rotate.getPid()) << std::endl;
            rotate.setState(READY);
            rotate.incrementPC();
            if(this->algorithmToUse == MULTILEVEL_FEEDBACK_QUEUE) {
                switch (rotate.getLastQueue()) {
                case 0:
                    this->readyQueue->enqueueProcess(rotate);
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
            CPU::getInstance().mutexLock->unlock();
        }
    }
}
