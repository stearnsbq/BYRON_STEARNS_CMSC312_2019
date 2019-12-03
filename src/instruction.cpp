#include "instruction.hpp"

Instruction::Instruction(std::string instr, int burst, TYPE type, bool critical)
{
    this->instr = instr;
    this->burst = burst;
    this->type = type;
    this->critical = critical;
}

Instruction::Instruction(std::string instr, std::string out, TYPE type)
{
    if(type == OUT) {
        this->instr = instr;
        this->out = out;
        this->burst = 1;
        this->type = type;
    }else if (type == SEND) {
        this->instr = instr;
        this->msg = out;
        this->burst = 1;
        this->type = type;
    }

}

Instruction::Instruction(std::string instr, TYPE type){

    this->instr = instr;
    this->burst = 1;
    this->type = type;
}

Instruction::Instruction()
{
    this->instr = "";
    this->burst = 0;
}

Instruction::~Instruction()
{
    this->instr.clear();
    this->out.clear();
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

void Instruction::decBurst()
{
    this->burst--;
}

std::string Instruction::getMsg(){
    return this->msg;
}

bool Instruction::isCritical(){
    return this->critical;
}

std::string Instruction::getOut(){
    return this->out;
}
void Instruction::setOut(std::string out){
    this->out = out;
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
