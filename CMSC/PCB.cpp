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


void Process::addInstruction(std::string instr){
        Instruction newInstr;
    if (instr.find("CALCULATE") != std::string::npos){
        int burst = stoi(instr.substr(instr.find(" ")));
        newInstr = Instruction("CALULATE", burst, CALCULATE);
    }else if(instr.find("I/O") != std::string::npos){
        int burst = stoi(instr.substr(instr.find(" ")));
        newInstr = Instruction("I/O", burst, CALCULATE);
    }
    this->instructions.push_back(newInstr);
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

void Process::setName(std::string name)
{
    this->name = name;
}
std::string Process::getName()
{
    return this->name;
}

void Process::setPC(int pc)
{
    this->pc = pc;
}

void Process::operator++()
{
    this->pc++;
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
