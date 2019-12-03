#include "PCB.hpp"
#include <ctime>
#include <memory>


Process::Process()
{
    this->pc = 0;
    this->pid = 0;
    this->priority = -1;
    this->lastQueue = 0;
    this->parent = nullptr;
    this->child = nullptr;


}

Process::Process(Process * parent){
    this->pc = parent->pc;
    this->priority = parent->priority <= 0 ?  0 : parent->priority -1;
    this->lastQueue = 0;
    this->parent = parent;
    this->child = nullptr;
    this->cycles = parent->cycles;
    this->memory = parent->memory;
    this->name = parent->name;
    this->instructions = parent->instructions;
    this->currInstr = parent->currInstr;
}

Process::~Process()
{
    this->instructions.clear();
}


bool operator<(Process const&p1, Process const&p2){
    return p1.priority < p2.priority;
}

bool operator>(Process const&p1, Process const&p2){
    return p1.priority < p2.priority;
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

void Process::addInstruction(QJsonObject instr, bool toRandom)
{
    Instruction newInstr;
    if (instr["Type"] == "CALCULATE")
    {

        if(toRandom) {
            instr["Burst"] = (std::rand() % instr["Burst"].toInt()) + 1;
            this->setCycles(this->getCycles() + instr["Burst"].toInt());
        }

        newInstr = Instruction("CALCULATE", instr["Burst"].toInt(), CALCULATE, false);

    }
    else if (instr["Type"] == "I/O")
    {
        if(toRandom) {
            instr["Burst"] = (std::rand() % instr["Burst"].toInt()) + 1;
        }

        newInstr = Instruction("I/O", instr["Burst"].toInt(), IO, false);

    }else if (instr["Type"] == "OUT") {

        newInstr = Instruction("OUT", instr["Out"].toString().toStdString(), OUT);

    } else if (instr["Type"] == "YIELD") {

        newInstr = Instruction("YIELD", YIELD);

    }else if (instr["Type"] == "FORK") {

        newInstr = Instruction("FORK", FORK);

    }else if (instr["Type"] == "CRITICAL_IO") {

        if(toRandom) {

            instr["Burst"] = (std::rand() % instr["Burst"].toInt()) + 1;

        }

        newInstr = Instruction("CRITICAL_IO", instr["Burst"].toInt(), CRITICAL_IO, true);

    }else if (instr["Type"] == "CRITICAL_CALCULATE") {

        if(toRandom) {
            instr["Burst"] = (std::rand() % instr["Burst"].toInt()) + 1;
            this->setCycles(this->getCycles() + instr["Burst"].toInt());
        }

        newInstr = Instruction("CRITICAL_CALCULATE", instr["Burst"].toInt(), CRITICAL_CALC, true);

    }else if (instr["Type"] == "SEND") {

        newInstr = Instruction("SEND", instr["Msg"].toString().toStdString(), SEND);

    }else if ( instr["Type"] == "RECIEVE") {

        newInstr = Instruction("RECIEVE",  RECIEVE);

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

Process * Process::getChild(){
    return this->child;
}

void Process::setChild(Process *child){
    this->child = child;
}

void Process::setParent(Process *parent){
    this->parent = parent;
}

Process * Process::getParent(){
    return this->parent;
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
    const std::vector<std::string> strings = {"NEW", "READY","RUN","WAIT","EXIT", "WAITING FOR CHILD", "WAITING FOR MESSAGE"};
    return QString::fromUtf8(strings.at(this->state).c_str());
}

void Process::setState(PROCESS_STATE state)
{
    this->state = state;
}
int Process::getPriority()
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

QString Process::toString(){
    QString str = "======PROCESS======\nNAME: " + QString::fromUtf8(this->name.c_str()) + "\nPID: " + QString::number(pid) + "\nPRIORITY: " + QString::number(priority)+ "\nSTATE: " + this->getStateString() + "\nPC: " + QString::number(pc) + "\nMEMORY: " + QString::number(memory) + "\nCYCLES: " + QString::number(cycles) +"\n===================";
    return str;
}
