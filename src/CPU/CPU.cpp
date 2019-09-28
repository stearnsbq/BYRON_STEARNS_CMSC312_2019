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

void CPU::clockThread(std::function<void()> func)
{
    while (this->isRunning)
    {
        // std::cout << "cpu tick" << std::endl;
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
    this->clock_thread = std::thread(clockThread, this, func);
}

void CPU::allocateMemory(size_t amount)
{
    // this->memory->alloc(amount);
}