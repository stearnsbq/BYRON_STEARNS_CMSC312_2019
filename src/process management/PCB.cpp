#include "PCB.hpp"

Process::Process()
{
}

Process::~Process()
{
}

unsigned int Process::getPid()
{
    return this->pid;
}

void Process::setCycles(int cycles)
{
    this->cycles = cycles;
}

void Process::setMemoryReq(int size)
{
    this->memory = size;
}

void Process::setPriority(int p)
{
    this->priority = p;
}

void Process::setPC(int pc)
{
    this->pc = pc;
}

PROCESS_STATE Process::getState()
{
    return this->state;
}
void Process::setState(PROCESS_STATE state)
{
    this->state = state;
}
unsigned int Process::getPriority()
{
    return this->priority;
}
int Process::getMemoryReq()
{
    return this->memory;
}
int Process::getCycles()
{
    return this->cycles;
}
int Process::getProgramCounter()
{
    return this->pc;
}
