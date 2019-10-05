#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

enum TYPE
{
    CRITICAL_CALC,
    CRITICAL_IO,
    CALCULATE,
    IO,
    OUT,
    NOP
};

class Instruction
{
private:
    std::string instr;
    std::string out;
    int burst;
    TYPE type;

public:
    void decBurst();
    Instruction(std::string instr, int burst, TYPE type);
     Instruction(std::string instr, std::string out, TYPE type);
    Instruction();
    ~Instruction();
    std::string getInstr();
    int getBurst();
    TYPE getType();
    std::string getOut();
    void setOut(std::string out);
    void setInstr(std::string instr);
    void setBurst(int burst);
    void setTYPE(TYPE type);
};

#endif
