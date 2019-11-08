#include "PCB.hpp"
#include <ctime>


Process::Process()
{
    this->pc = 0;
    this->pid = 0;
    this->priority = 0;
    this->lastQueue = 0;


}

Process::~Process()
{
}


Instruction Process::getCurrentInstruction()
{
    return this->instructions.at(this->pc);
}

TYPE Process::getCurrentInstructionType(){
    return this->instructions.at(this->pc).getType();
}

unsigned int Process::getPid()
{
    return this->pid;
}


int Process::getLastQueue(){
    return this->lastQueue;
}

void Process::setLastQueue(int qNum){
    this->lastQueue = qNum;
}

void Process::incrementPC()
{
    this->pc++;
}

int Process::getMemoryReq(){
    return this->memory;
}

void Process::setMemoryReq(int amount){
    this->memory = amount;
}

void Process::addInstruction(std::string instr, bool toRandom)
{
    Instruction newInstr;
    if (instr.find("CALCULATE") != std::string::npos)
    {
        int burst = stoi(instr.substr(instr.find(" ")));
        if(toRandom) {
            burst = std::rand() % burst + 1;
            this->setCycles(this->getCycles() + burst);
        }
        if(instr.find("CRITICAL") != std::string::npos) {
            newInstr = Instruction("CRITICAL_CALCULATE", burst, CRITICAL_CALC, true);
        }else{
            newInstr = Instruction("CALCULATE", burst, CALCULATE, false);
        }

    }
    else if (instr.find("I/O") != std::string::npos)
    {
        int burst = stoi(instr.substr(instr.find(" ")));
        if(toRandom) {
            burst = std::rand() % burst + 1;
        }
        if(instr.find("CRITICAL") != std::string::npos) {
            newInstr = Instruction("CRITICAL_I/O", burst, CRITICAL_IO, true);
        }else{
            newInstr = Instruction("I/O", burst, IO, false);
        }
    }else if (instr.find("OUT") != std::string::npos) {
        std::string print = instr.substr(instr.find(" "));
        newInstr = Instruction("OUT", print, OUT);
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
    if(this->pc > this->instructions.size() -1) {
        return 0;
    }else{
        return this->instructions.at(this->pc).getBurst();
    }

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

QString Process::getStateString(){
    const char * strings[] = {"NEW", "READY","RUN","WAIT","EXIT"};
    return QString::fromUtf8(strings[this->state]);
}

void Process::setState(PROCESS_STATE state)
{
    this->state = state;
}
unsigned int Process::getPriority()
{
    return this->priority;
}

int Process::getCycles()
{
    return this->cycles;
}
int Process::getProgramCounter()
{
    return this->pc;
}
