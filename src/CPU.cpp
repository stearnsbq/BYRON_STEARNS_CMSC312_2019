#include "CPU.hpp"
#include <csignal>

CPU::CPU()
{
    this->memory = new mainmemory(4096000, 4.0);
    this->isRunning = true;
    this->timeQuantum = 0;
    this->runningProcess.setState(EXIT);
}

long long CPU::availableMemory(){
    return 1000;
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
    while(!kernel::getInstance().isFinished()) {
        cycle();
        if(unit == "ms") {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }else if(unit == "ns") {
            std::this_thread::sleep_for(std::chrono::nanoseconds(time));
        }else{
            std::this_thread::sleep_for(std::chrono::seconds(time));
        }
    }
    kernel::getInstance().window->done();
    this->timeQuantum = 0;
    return;
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

