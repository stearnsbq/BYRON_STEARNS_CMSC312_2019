#include "shorttermscheduler.h"
#include "mainwindow.h"



ShortTermScheduler::ShortTermScheduler(ALGORITHM algoToUse, Core & parent) : parent(parent) {
    this->algorithmToUse = algoToUse;
    this->totalProcesses = 0;
    this->dp = new Dispatcher(parent);
}



void ShortTermScheduler::runScheduler(){
    emit kernel::getInstance().window->setLoad(parent.coreNum,totalProcesses);
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
    std::lock_guard<std::mutex> lock(_migrateLock);
    switch (q) {
    case WAITING:
        this->waitingQueue.push(p);
        break;
    case MID:
        this->midLevel.push(p);
        this->totalProcesses++;
        break;
    case READY_Q:
        this->readyQueue.push(p);
        this->totalProcesses++;
        break;
    case BASE:
        this->baseLevel.push(p);
        this->totalProcesses++;
        break;
    }
}



Process ShortTermScheduler::determineProcessForMigrate(){
    std::lock_guard<std::mutex> lock(_migrateLock);
    if(!this->readyQueue.empty()) {
        Process toMigrate = this->readyQueue.top();
        this->readyQueue.pop();
        this->totalProcesses--;
        return toMigrate;
    }else if(!this->midLevel.empty() ) {
        Process toMigrate = this->midLevel.top();
        this->midLevel.pop();
        this->totalProcesses--;
        return toMigrate;
    }else if (!this->baseLevel.empty()) {
        Process toMigrate = this->baseLevel.top();
        this->baseLevel.pop();
        this->totalProcesses--;
        return toMigrate;
    }
    emit kernel::getInstance().window->setLoad(parent.coreNum,totalProcesses);
    return Process();
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
    std::lock_guard<std::mutex> lock(_migrateLock);
    std::priority_queue<Process, std::vector<Process> > * queueToProcess = nullptr;
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
            Process newProcess = queueToProcess->top();
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
                this->midLevel.push(rotate);
                break;
            case 1:
                this->baseLevel.push(rotate);
                break;
            case 2:
                this->baseLevel.push(rotate);
                break;
            }

        }


    }
    this->timeQuantum++;
}



void ShortTermScheduler::roundRobin()
{
    std::lock_guard<std::mutex> lock(_migrateLock);
    if (parent.runningProcess.getState() == EXIT && !this->readyQueue.empty())
    {
        this->timeQuantum = 0;
        Process newProcess = this->readyQueue.top();
        this->readyQueue.pop();
        newProcess.setState(RUN);
        parent.runningProcess = newProcess;
        kernel::getInstance().updateProcessTable(newProcess);
    }

    if (this->timeQuantum >= 20)
    {
        Process rotate = parent.runningProcess;
        parent.runningProcess.setState(EXIT);
        rotate.setState(READY);
        this->readyQueue.push(rotate);
        kernel::getInstance().updateProcessTable(rotate);
        this->timeQuantum = 0;
    }

    this->timeQuantum++;
}


void ShortTermScheduler::processWaitingQueue()
{
    if(!this->waitingQueue.empty()) {


        if(this->waitingQueue.front().getState() == WAITING_FOR_CHILD) {
            std::cout << "waiting on child" << std::endl;
            if(this->waitingQueue.front().getChild() != nullptr && this->waitingQueue.front().getChild()->getState() == EXIT) {
                std::cout << "child exited" << std::endl;
                Process rotate = this->waitingQueue.front();
                this->waitingQueue.pop();
                CPU::getInstance().free(rotate.pages);
            }

        }else if(this->waitingQueue.front().getState() == WAITING_FOR_MSG) {
            if(!kernel::getInstance().mailBox->empty()) {
                mailbox::message msg = kernel::getInstance().mailBox->recieveMessage();
                emit kernel::getInstance().window->print(msg.msg);
                std::cout << "RECIEVED MESSAGE " + msg.msg + " FROM PID: " + std::to_string(msg.originPid) << std::endl;
                Process rotate = this->waitingQueue.front();
                rotate.incrementPC();
                this->waitingQueue.pop();
                this->readyQueue.push(rotate);
            }
        }else{

            if(this->waitingQueue.front().getCurrentBurst() > 0) {

                this->waitingQueue.front().decrementBurst();

            }else{

                Process rotate = this->waitingQueue.front();
                this->waitingQueue.pop();

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

                if(rotate.getInstructions().size() - 1 > rotate.getProgramCounter() && rotate.getCurrentInstruction().isCritical()) {
                    CPU::getInstance().mutexLock->unlock();
                    emit kernel::getInstance().window->setCritical(false);
                }

            }
        }
    }




}
