#include "CPU.hpp"
#include <csignal>
#include <chrono>
CPU::CPU() : memoryMutex()
{
    this->memory = new mainmemory(4096000, 1024.0);
    this->logicalAddr = 0x40000;
    this->runningProcess.setState(EXIT);
    this->mutexLock = new mutex();
}


long long CPU::availableMemory(){
    return this->memory->availableMemory();
}

Process& CPU::getRunningProcess(){
    return this->runningProcess;
}

void CPU::setRunningProcess(Process p){
    this->runningProcess = p;
}

void CPU::run(int time, QString unit, ALGORITHM algoToUse)
{
    this->core1 = new Core(1, algoToUse);
    this->core2 = new Core(2, algoToUse);

    this->core1->start(time, unit);
    this->core2->start(time, unit);

    std::thread balancer(&CPU::loadBalancer, this, time, unit);
    balancer.detach();
}



void CPU::start(int time, QString unit, ALGORITHM algo)
{
    this->runningProcess.setState(EXIT);
    this->run(time, unit, algo);
}

unsigned int CPU::getNextLogicalAddr(){
    return this->logicalAddr += 0x400;
}

int CPU::getNextOpenFrame(){
    return this->memory->getNextFrame();
}

void CPU::setPagesDirty(std::vector<page> pages){
    this->memory->setPagesDirty(pages);
}

std::vector<page> CPU::alloc(unsigned int size){
    std::lock_guard<std::mutex> lock(this->memoryMutex);

    return this->memory->allocateMemory(size);

}

void CPU::migrateProcess(Process p, Core * coreToMigrateTo){
    coreToMigrateTo->addProcess(p);
}


void CPU::sleep(int time, QString unit){
    if(unit == "ms") {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }else if(unit == "ns") {
        std::this_thread::sleep_for(std::chrono::nanoseconds(time));
    }else{
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }
}


void CPU::loadBalancer(int time, QString unit){
    while(!kernel::getInstance().shutDown) {

        while(core1->getLoad() > core2->getLoad() + 1 && (core2->getLoad() > 0)) {
            Process toMigrate = core1->migrate();
            if(toMigrate.getPriority() > 0) {
                this->migrateProcess(toMigrate, core2);
            }
            sleep(time, unit);
        }

        while(core2->getLoad() > core1->getLoad() + 1 && (core1->getLoad() > 0)) {
            Process toMigrate = core2->migrate();
            if(toMigrate.getPriority() > 0) {
                this->migrateProcess(toMigrate, core1);
            }
            sleep(time, unit);
        }
        sleep(time, unit);
    }
}

void CPU::free(std::vector<page> pages){
    std::lock_guard<std::mutex> lock(this->memoryMutex);
    this->memory->freeMemory(pages);
}


