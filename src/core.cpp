#include "core.h"
#include "kernel.h"
#include "mutex.h"

Core::Core(int coreNumber, ALGORITHM algoToUse)
{
    this->coreNum = coreNumber;
    this->shortTerm = new ShortTermScheduler(algoToUse, *this);
    this->longTerm = new LongTermScheduler(shortTerm);
    this->ltTimer = 10;
    this->shortTermAlgorithm = algoToUse;
    this->runningProcess.setState(EXIT);
}


Core::~Core(){

}

int Core::getLoad(){
    return this->shortTerm->totalProcesses;
}

Process Core::migrate(){
    return this->shortTerm->determineProcessForMigrate();
}

void Core::addProcess(Process p){
    this->shortTerm->enqueueProcess(p, READY_Q);
}


void Core::start(int time, QString unit){
    std::thread schedulerThread = std::thread(&Core::run, this, time, unit);
    schedulerThread.detach();
    std::thread coreThread = std::thread(&Core::cycle, this);
    coreThread.detach();
}


void Core::sleep(){
    if(unit == "ms") {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }else if(unit == "ns") {
        std::this_thread::sleep_for(std::chrono::nanoseconds(time));
    }else{
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }
}

void Core::run(int time, QString unit){
    this->time = time;
    this->unit = unit;
    while(!kernel::getInstance().isFinished()) {
        if(ltTimer >= 10) {
            this->longTerm->runScheduler();
            ltTimer = 0;
        }
        this->shortTerm->runScheduler();
        ltTimer++;
        sleep();
    }

    kernel::getInstance().window->done();
}


void Core::cycle(){
    while(!kernel::getInstance().isFinished()) {
        executeOperation();
        sleep();
    }
}


void Core::iO(){
    Process rotate = runningProcess;

    rotate.setState(WAIT);

    kernel::getInstance().updateProcessTable(rotate);

    runningProcess.setState(EXIT);

    this->shortTerm->enqueueProcess(rotate, WAITING);
}

void Core::criticalSection(){



    if(runningProcess.getCurrentInstructionType() == CRITICAL_CALC) {

        std::string str = "PID: " + std::to_string(runningProcess.getPid()) + " ENTERED CRITICAL SECTION";

        emit kernel::getInstance().window->print(str);

        if(CPU::getInstance().mutexLock->lock() == 0) {


            unsigned int timeOut = 0;
            emit kernel::getInstance().window->setCritical(true);
            while(runningProcess.getCurrentBurst() > 0) {

                std::string str = runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(runningProcess.getCurrentBurst());

                emit kernel::getInstance().window->print(str);

                runningProcess.decrementBurst();

                sleep();

                if(timeOut >= 60) {
                    emit kernel::getInstance().window->print("critical section timeout");
                    break;
                }
                timeOut++;
            }

            CPU::getInstance().mutexLock->unlock();
            emit kernel::getInstance().window->setCritical(false);
        }
    } else if(runningProcess.getCurrentInstructionType() == CRITICAL_IO) {

        std::string str = "PID: " + std::to_string(runningProcess.getPid()) + " ENTERED CRITICAL SECTION";

        emit kernel::getInstance().window->print(str);

        if(CPU::getInstance().mutexLock->lock() != 0) {

            std::string str = "Process tried to enter critical second however it timed out trying again....";

            emit kernel::getInstance().window->print(str);

        }else{
            emit kernel::getInstance().window->setCritical(true);
            Process rotate = runningProcess;

            rotate.setState(WAIT);

            kernel::getInstance().updateProcessTable(rotate);

            runningProcess.setState(EXIT);

            this->shortTerm->enqueueProcess(rotate, WAITING);
        }
    }

}

void Core::calculate(){
    std::string str = "RUNNING!! PID: " + std::to_string(runningProcess.getPid()) + " ON CORE: " + std::to_string(coreNum) + " " + runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(runningProcess.getCurrentBurst());
    emit kernel::getInstance().window->print(str);
    std::cout << str << std::endl;

    runningProcess.decrementBurst();
}

void Core::yield(){
    runningProcess.incrementPC();
    Process yield = runningProcess;

    yield.setState(READY);

    kernel::getInstance().updateProcessTable(yield);

    runningProcess.setState(EXIT);

    this->shortTerm->enqueueProcess(yield, READY_Q);
}

void Core::out(){
    emit kernel::getInstance().window->print(runningProcess.getCurrentInstruction().getOut());
}

void Core::send(){
    kernel::getInstance().mailBox->newMessage(runningProcess.getCurrentInstruction().getMsg(), runningProcess.getPid());
    runningProcess.incrementPC();
}

void Core::recieve(){
    if(!kernel::getInstance().mailBox->empty()) {
        mailbox::message msg =  kernel::getInstance().mailBox->recieveMessage();
        emit kernel::getInstance().window->print(msg.msg);
        std::cout << "RECIEVED MESSAGE " + msg.msg + " FROM PID: " + std::to_string(msg.originPid) << std::endl;
    }else{
        Process yield = runningProcess;

        yield.setState(WAITING_FOR_MSG);

        kernel::getInstance().updateProcessTable(yield);

        runningProcess.setState(EXIT);

        this->shortTerm->enqueueProcess(yield, WAITING);

    }
}


void Core::fork(){
    runningProcess.incrementPC();
    std::cout << "FORKING" << std::endl;
    Process * parent = new Process();
    *parent = runningProcess;
    Process child = parent;
    child.setParent(parent);
    parent->setChild(&child);
    kernel::getInstance().newProcess(child);
}



void Core::executeOperation(){

    if(runningProcess.getState() != EXIT) {
        CPU::getInstance().setPagesDirty(runningProcess.pages);
        if(runningProcess.getCurrentBurst() > 0) {

            switch (runningProcess.getCurrentInstructionType()) {
            case OUT:
                out();
                break;
            case IO:
                iO();
                break;
            case CALCULATE:
                calculate();
                break;
            case YIELD:
                yield();
                break;
            case CRITICAL_IO:
            case CRITICAL_CALC:
                criticalSection();
                break;
            case FORK:
                fork();
                break;
            case SEND:
                send();
                break;
            case RECIEVE:
                recieve();
                break;
            }

        }else if(runningProcess.getInstructions().size() - 1 > runningProcess.getProgramCounter()) {

            runningProcess.incrementPC();

        }else{

            if(runningProcess.getChild() != nullptr && runningProcess.getChild()->getState() != EXIT) {

                Process rotate = runningProcess;
                rotate.setState(WAITING_FOR_CHILD);
                kernel::getInstance().updateProcessTable(rotate);
                runningProcess.setState(EXIT);
                this->shortTerm->enqueueProcess(rotate, WAITING);
            }else{
                Process rotate = runningProcess;
                rotate.setState(EXIT);
                kernel::getInstance().updateProcessTable(rotate);
                CPU::getInstance().free(rotate.pages);
                runningProcess.setState(EXIT);
                runningProcess.setChild(nullptr);
                runningProcess.setParent(nullptr);
                this->shortTerm->totalProcesses--;
                CPU::getInstance().setPagesDirty(runningProcess.pages);
                emit kernel::getInstance().window->setLoad(coreNum, this->shortTerm->totalProcesses);
            }

        }

    }
}
