#include "PCB.hpp"

Process::Process()
{
    this->pc = 0;
    this->pid = 0;
    this->priority = 0;
}

Process::~Process()
{
}

Instruction Process::getCurrentInstruction()
{
    return this->currInstr;
}

unsigned int Process::getPid()
{
    return this->pid;
}

void Process::incrementPC()
{
    this->pc++;

}

void Process::addInstruction(std::string instr)
{

    Instruction newInstr;
    if (instr.find("CALCULATE") != std::string::npos)
    {
        int burst = stoi(instr.substr(instr.find(" ")));
        newInstr = Instruction("CALULATE", burst, CALCULATE);
    }
    else if (instr.find("I/O") != std::string::npos)
    {
        int burst = stoi(instr.substr(instr.find(" ")));
        newInstr = Instruction("I/O", burst, IO);
    }
    this->instructions.push_back(newInstr);
    this->currInstr = this->instructions.at(this->pc);
}

void Process::setCycles(int cycles)
{
    this->cycles = cycles;
}

void Process::decrementBurst()
{
    this->instructions.at(this->pc).decBurst();
}

void Process::setMemoryReq(int size)
{
    this->memory = size;
}

void Process::setPid(int pid){
    this->pid = pid;
}

std::vector<Instruction> Process::getInstructions()
{
    return this->instructions;
}

void Process::setPriority(int p)
{
    this->priority = p;
}

int Process::getCurrentBurst()
{

    return this->instructions.at(this->pc).getBurst();
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
