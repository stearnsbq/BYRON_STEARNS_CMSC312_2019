#include "kernel.h"


kernel::kernel()
{

    this->longTermTimer = 0;
    this->shutDown = false;
    this->pidCounter = 0;
    this->mailBox = new mailbox();

}

void kernel::updateProcessTable(Process p){

    this->processTable[p.getPid()] = p;
    emit window->updateProcessListGUI(p);

}

void kernel::newProcess(Process & p){

    p.setState(NEW);
    p.setPid(getNextPid());
    this->jobPool.push(p);
    this->processTable.insert(std::make_pair(p.getPid(), p));
    emit window->updateProcessListGUI(p);

}




int kernel::getNextPid(){

    if(pidCounter >= 32768) {
        pidCounter = 0;
    }
    return pidCounter++;
}



bool kernel::compare( Process& p1,  Process& p2){

    return p1.getPriority() < p2.getPriority();

}

bool kernel::isFinished(){

    return this->shutDown;

}

Process kernel::getNextProcessInPool(){

    std::lock_guard<std::mutex> lock{this->jobPoolMutex};

    if(!this->jobPool.empty()) {

        Process p = this->jobPool.top();
        this->jobPool.pop();

        return p;
    }

    return Process();
}

bool kernel::isJobPoolEmpty(){

    return this->jobPool.empty();
}


std::unordered_map<int, Process> kernel::getListOfProcesses(){

    return this->processTable;
}



