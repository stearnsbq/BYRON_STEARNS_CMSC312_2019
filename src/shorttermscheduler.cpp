#include "shorttermscheduler.h"
#include "mainwindow.h"


ShortTermScheduler::ShortTermScheduler() : ShortTermScheduler(ROUND_ROBIN)
{

}

ShortTermScheduler::ShortTermScheduler(ALGORITHM algoToUse)
{
    this->algorithmToUse = algoToUse;
    this->readyQueue = new Queue();
    this->midLevel = new Queue();
    this->baseLevel = new Queue();
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
}

void ShortTermScheduler::enqueueProcess(Process p){
    this->readyQueue->enqueueProcess(p);
}

void ShortTermScheduler::feedBackQueue(){
    if(!this->readyQueue->isEmpty()) {
        this->roundRobinProcess(0, 8);
    }else if(!this->midLevel->isEmpty()) {
        this->roundRobinProcess(1, 16);
    }else{
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
            CPU::getInstance().setRunningProcess(this->readyQueue->dequeueProcess());
            CPU::getInstance().getRunningProcess().setLastQueue(queue);
            CPU::getInstance().getRunningProcess().setState(RUN);
        }

        if(this->timeQuantum >= timeQ) {

            Process rotate = CPU::getInstance().getRunningProcess();
            rotate.setState(READY);
            CPU::getInstance().getRunningProcess().setState(EXIT);
            switch (queue) {
            case 0:
                //emit m->print("Process q1 -> q2");
                this->midLevel->enqueueProcess(rotate);
                break;
            case 1:
                //emit m->print("Process q2 -> q3");
                this->baseLevel->enqueueProcess(rotate);
                break;
            case 2:
                //emit m->print("preempt to back");
                this->baseLevel->enqueueProcess(rotate);
                break;
            }

        }else{
            if(CPU::getInstance().getRunningProcess().getCurrentBurst() > 0) {
                if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == OUT) {
                    //emit m->print(this->runningProcess.getCurrentInstruction().getOut());
                }else if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == IO) {
                    // emit m->print("IO, PREEMPT INTO WAITING QUEUE");
                    Process rotate = CPU::getInstance().getRunningProcess();
                    rotate.setState(WAIT);
                    CPU::getInstance().getRunningProcess().setState(EXIT);
                    //this->waitingQueue->enqueueProcess(rotate);
                }else{
                    // std::string str = "RUNNING!! PID: " + std::to_string(this->runningProcess.getPid()) + " " + this->runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(this->runningProcess.getCurrentBurst());
                    // emit kernel::getInstance().window->print(str);
                    CPU::getInstance().getRunningProcess().decrementBurst();
                }
            }else if(CPU::getInstance().getRunningProcess().getInstructions().size() - 1 > CPU::getInstance().getRunningProcess().getProgramCounter()) {
                CPU::getInstance().getRunningProcess().incrementPC();
            }else{
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
            if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == OUT) {

            }else if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == IO) {

                Process rotate = CPU::getInstance().getRunningProcess();
                rotate.setState(WAIT);
                CPU::getInstance().getRunningProcess().setState(EXIT);
                //this->waitingQueue->enqueueProcess(rotate);
            }else{

                std::string str = "RUNNING!! PID: " + std::to_string(CPU::getInstance().getRunningProcess().getPid()) + " " + CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr() + " burst #" + std::to_string(CPU::getInstance().getRunningProcess().getCurrentBurst());
                std::cout << str << std::endl;
                emit kernel::getInstance().window->print(str);
                CPU::getInstance().getRunningProcess().decrementBurst();
            }
        }
        else if (CPU::getInstance().getRunningProcess().getInstructions().size() - 1 > CPU::getInstance().getRunningProcess().getProgramCounter()) // if instruction is done increment PC
        {
            std::string out =   "PC " + std::to_string(CPU::getInstance().getRunningProcess().getProgramCounter()) + " instr: " + CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr();
            //emit m->print(out);
            emit kernel::getInstance().window->print(out);
            CPU::getInstance().getRunningProcess().incrementPC();
        }else{ // process is done exit
            Process rotate = CPU::getInstance().getRunningProcess();
            rotate.setState(EXIT);

            CPU::getInstance().getRunningProcess().setState(EXIT);
        }
        kernel::getInstance().updateProcessTable( CPU::getInstance().getRunningProcess().getPid(),  CPU::getInstance().getRunningProcess());
    }

    this->timeQuantum++;
}
