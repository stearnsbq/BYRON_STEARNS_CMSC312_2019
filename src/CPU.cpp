#include "CPU.hpp"
#include <csignal>
using namespace std;

CPU *cpu = new CPU();

CPU::CPU()
{
    this->memory = new Memory();
    this->isRunning = true;
    this->timeQuantum = 0;

}
int CPU::getTimeQ()
{
    return this->timeQuantum;
}

void CPU::handler(int sig)
{
    this->isRunning = false;
}

CPU::~CPU()
{
    this->isRunning = false;
}

Memory * CPU::getMemory(){
    return this->memory;
}

void CPU::freeMemory(Memory::Block * ptr){
    this->memory->freeMemory(ptr);
}

long long CPU::availableMemory()
{
    return this->memory->availableMemory();
}

void CPU::run()
{
    while (this->isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(this->clockTime));
    }
    return;
}

void CPU::setTimeQ(int time)
{
    this->timeQuantum = time;
}

void CPU::start()
{
    this->clock_thread = std::thread(&CPU::run, this);
    this->clock_thread.join();
}

Memory::Block * CPU::allocateMemory(size_t amount)
{
    return this->memory->alloc(amount);
}
