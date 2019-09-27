#include "instruction.hpp"

Instruction::Instruction(std::string instr, int burst, TYPE type)
{
    this->instr = instr;
    this->burst = burst;
    this->type = type;
}
Instruction::Instruction()
{
}
Instruction::~Instruction()
{
    this->instr.clear();
}

std::string Instruction::getInstr()
{
    return this->instr;
}
int Instruction::getBurst()
{
    return this->burst;
}
TYPE Instruction::getType()
{
    return this->type;
}

void Instruction::operator--()
{
    this->burst--;
}

void Instruction::setInstr(std::string instr)
{
    this->instr = instr;
}
void Instruction::setBurst(int burst)
{
    this->burst = burst;
}
void Instruction::setTYPE(TYPE type)
{
    this->type = type;
}