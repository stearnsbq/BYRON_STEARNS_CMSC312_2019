#include "CPU.hpp"
#include <csignal>

CPU::CPU() : memoryMutex()
{
    this->memory = new mainmemory(4096000, 1024.0);
    this->isRunning = true;
    this->logicalAddr = 0x40000;
    this->timeQuantum = 0;
    this->runningProcess.setState(EXIT);
    this->mutexLock = new mutex();
    this->core1 = new Core(1);
    this->core2 = new Core(2);

}

long long CPU::availableMemory(){
    return this->memory->availableMemory();
}

int CPU::getTimeQ()
{
    return this->timeQuantum;
}

CPU::~CPU()
{
    this->isRunning = false;
}

void CPU::setIsRunning(bool val){
    this->isRunning = val;
}

Process& CPU::getRunningProcess(){
    return this->runningProcess;
}

void CPU::setRunningProcess(Process p){
    this->runningProcess = p;
}

void CPU::run(int time, QString unit)
{
    this->core1->start(time, unit);
    this->core2->start(time, unit);
}

void CPU::cycle(){
    kernel::getInstance().schedule();
}

void CPU::setTimeQ(int time)
{
    this->timeQuantum = time;
}

void CPU::start(int time, QString unit)
{
    this->runningProcess.setState(EXIT);
    this->run(time, unit);
}

unsigned int CPU::getNextLogicalAddr(){
    return this->logicalAddr += 0x400;
}

unsigned int CPU::getNextOpenFrame(){
    return this->memory->getNextFrame();
}

std::vector<page> CPU::alloc(unsigned int size){
    std::lock_guard<std::mutex> lock(this->memoryMutex);
    if(size >= this->availableMemory()) {
        std::vector<page> empty;
        return empty;
    }else{
        emit kernel::getInstance().window->updateMemoryBarGUI(size);
        return this->memory->allocateMemory(size);
    }
}

void CPU::free(std::vector<page> pages){
    std::lock_guard<std::mutex> lock(this->memoryMutex);
    this->memory->freeMemory(pages);
}

void CPU::executeInstruction(unsigned int timeQ){
    if(this->getRunningProcess().getState() != EXIT) {
        if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == OUT) {

            emit kernel::getInstance().window->print(CPU::getInstance().getRunningProcess().getCurrentInstruction().getOut());
            // refactor this
        }else if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == IO) {

            Process rotate = CPU::getInstance().getRunningProcess();

            rotate.setState(WAIT);

            kernel::getInstance().updateProcessTable(rotate);

            CPU::getInstance().getRunningProcess().setState(EXIT);

            kernel::getInstance().IOPreempt(rotate);

        }else if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == CRITICAL_CALC) {

            std::string str = "PID: " + std::to_string(CPU::getInstance().getRunningProcess().getPid()) + " ENTERED CRITICAL SECTION";

            emit kernel::getInstance().window->print(str);

            if(mutexLock->lock() != 0) {

                std::string str = "Process tried to enter critical second however it timed out trying again....";

                emit kernel::getInstance().window->print(str);

            }else{

                unsigned int timeOut = 0;
                while(CPU::getInstance().getRunningProcess().getCurrentBurst() > 0) {

                    // std::string str = CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr() + " burst #" + std::to_string(CPU::getInstance().getRunningProcess().getCurrentBurst());

                    //  emit kernel::getInstance().window->print(str);

                    CPU::getInstance().getRunningProcess().decrementBurst();

                    if(unit == "ms") {
                        std::this_thread::sleep_for(std::chrono::milliseconds(clockTime));
                    }else if(unit == "ns") {
                        std::this_thread::sleep_for(std::chrono::nanoseconds(clockTime));
                    }else{
                        std::this_thread::sleep_for(std::chrono::seconds(clockTime));
                    }

                    if(timeOut >= timeQ * 3) {
                        emit kernel::getInstance().window->print("critical section timeout");
                        break;
                    }
                    timeOut++;
                }

                mutexLock->unlock();
            }
        } else if(CPU::getInstance().getRunningProcess().getCurrentInstructionType() == CRITICAL_IO) {

            std::string str = "PID: " + std::to_string(CPU::getInstance().getRunningProcess().getPid()) + " ENTERED CRITICAL SECTION";

            emit kernel::getInstance().window->print(str);

            if(mutexLock->lock() != 0) {

                std::string str = "Process tried to enter critical second however it timed out trying again....";

                emit kernel::getInstance().window->print(str);

            }

            Process rotate = CPU::getInstance().getRunningProcess();

            rotate.setState(WAIT);

            kernel::getInstance().updateProcessTable(rotate);

            CPU::getInstance().getRunningProcess().setState(EXIT);

            kernel::getInstance().IOPreempt(rotate);

        }else{

            std::string str = "RUNNING!! PID: " + std::to_string(CPU::getInstance().getRunningProcess().getPid()) + " " + CPU::getInstance().getRunningProcess().getCurrentInstruction().getInstr() + " burst #" + std::to_string(CPU::getInstance().getRunningProcess().getCurrentBurst());
            // emit kernel::getInstance().window->print(str);
            std::cout << str << std::endl;
            CPU::getInstance().getRunningProcess().decrementBurst();
        }
    }

}

