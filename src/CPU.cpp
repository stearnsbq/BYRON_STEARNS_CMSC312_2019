#include "CPU.hpp"
#include <csignal>
using namespace std;

CPU *cpu = new CPU();

CPU::CPU()
{
    this->memory = new Memory();
    this->isRunning = true;
    //this->timeQuantum = 0;
    //signal(SIGINT, handler);
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

int CPU::availableMemory()
{
    return this->memory->availableMemory();
}

void CPU::clockThread(std::function<void()> func)
{
    while (this->isRunning)
    {
        func();
        std::this_thread::sleep_for(std::chrono::seconds(this->clockTime));
    }
    return;
}

void CPU::setTimeQ(int time)
{
    this->timeQuantum = time;
}

void CPU::clock(std::function<void()> func)
{
    this->clock_thread = std::thread(&CPU::clockThread, this, func);
}

Memory::Block * CPU::allocateMemory(size_t amount)
{
    return this->memory->alloc(amount);
}
