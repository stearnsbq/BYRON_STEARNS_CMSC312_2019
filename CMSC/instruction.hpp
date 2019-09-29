#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

enum TYPE
{
    CRITICAL_CALC,
    CRITICAL_IO,
    CALCULATE,
    IO
};

class Instruction
{
private:
    std::string instr;
    int burst;
    TYPE type;

public:
    void operator--();
    Instruction(std::string instr, int burst, TYPE type);
    Instruction();
    ~Instruction();
    std::string getInstr();
    int getBurst();
    TYPE getType();
    void setInstr(std::string instr);
    void setBurst(int burst);
    void setTYPE(TYPE type);
};

#endif