#include "core.h"
#include "kernel.h"
#include "mutex.h"

Core::Core(int coreNumber)
{
    this->coreNum = coreNumber;
    this->shortTerm = new ShortTermScheduler(MULTILEVEL_FEEDBACK_QUEUE, *this);
    this->longTerm = new LongTermScheduler(shortTerm);
    this->ltTimer = 10;
    this->runningProcess.setState(EXIT);
}


Core::~Core(){

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


void Core::executeOperation(){
    if(runningProcess.getState() != EXIT) {
        if(runningProcess.getCurrentInstructionType() == OUT) {

            emit kernel::getInstance().window->print(runningProcess.getCurrentInstruction().getOut());
            // refactor this
        }else if(runningProcess.getCurrentInstructionType() == IO) {

            Process rotate = runningProcess;

            rotate.setState(WAIT);

            kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);

            runningProcess.setState(EXIT);

            this->shortTerm->enqueueProcess(rotate, WAITING);


        }else if(runningProcess.getCurrentInstructionType() == CRITICAL_CALC) {

            std::string str = "PID: " + std::to_string(runningProcess.getPid()) + " ENTERED CRITICAL SECTION";

            emit kernel::getInstance().window->print(str);

            if(CPU::getInstance().mutexLock->lock() != 0) {

                std::string str = "Process tried to enter critical second however it timed out trying again....";

                emit kernel::getInstance().window->print(str);

            }else{

                unsigned int timeOut = 0;
                while(runningProcess.getCurrentBurst() > 0) {

                    // std::string str = runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(runningProcess.getCurrentBurst());

                    //  emit kernel::getInstance().window->print(str);

                    runningProcess.decrementBurst();

                    sleep();

                    if(timeOut >= 60) {
                        emit kernel::getInstance().window->print("critical section timeout");
                        break;
                    }
                    timeOut++;
                }

                CPU::getInstance().mutexLock->unlock();
            }
        } else if(runningProcess.getCurrentInstructionType() == CRITICAL_IO) {

            std::string str = "PID: " + std::to_string(runningProcess.getPid()) + " ENTERED CRITICAL SECTION";

            emit kernel::getInstance().window->print(str);

            if(CPU::getInstance().mutexLock->lock() != 0) {

                std::string str = "Process tried to enter critical second however it timed out trying again....";

                emit kernel::getInstance().window->print(str);

            }

            Process rotate = runningProcess;

            rotate.setState(WAIT);

            kernel::getInstance().updateProcessTable(rotate.getPid(),  rotate);

            runningProcess.setState(EXIT);

            this->shortTerm->enqueueProcess(rotate, WAITING);

        }else{

            std::string str = "RUNNING!! PID: " + std::to_string(runningProcess.getPid()) + " ON CORE: " + std::to_string(coreNum) + " " + runningProcess.getCurrentInstruction().getInstr() + " burst #" + std::to_string(runningProcess.getCurrentBurst());
            // emit kernel::getInstance().window->print(str);
            std::cout << str << std::endl;
            runningProcess.decrementBurst();
        }
    }
}
