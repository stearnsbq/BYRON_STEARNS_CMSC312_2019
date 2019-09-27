#include "CPU.hpp"
#include <csignal>
using namespace std;

CPU *cpu = new CPU();

CPU::CPU()
{
    this->memory = new Memory();
    this->isRunning = true;
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

int CPU::availableMemory()
{
    return 1000;
}

template <typename Function>
void CPU::clockThread(Function func)
{
    while (this->isRunning)
    {
        func();
        this_thread::sleep_for(chrono::seconds(this->clockTime));
    }
    return 1;
}

void CPU::setTimeQ(int time)
{
    this->timeQuantum = time;
}

template <typename Function>
void CPU::clock(Function func)
{
    this->clock_thread = thread(clockThread, func);
}

void CPU::allocateMemory(size_t amount)
{
    // this->memory->alloc(amount);
}