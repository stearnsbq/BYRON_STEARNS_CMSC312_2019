#ifndef PROCESS
#define PROCESS
#include <vector>
#include <iostream>
#include <string>
#include "memory.hpp"
#include "instruction.hpp"
typedef enum PROCESS_STATE
{
    NEW,
    READY,
    RUN,
    WAIT,
    EXIT
} PROCESS_STATE;

class Process
{
private:
    unsigned int pid;
    std::string name;
    std::vector<Instruction> instructions;
    Process * parent;
    Instruction currInstr;
    PROCESS_STATE state;
    unsigned int priority;
    int cycles;
    int pc;
    int memory;
    int lastQueue;
    Memory::Block * memoryLoc;

public:
    Process();
    ~Process();
    Instruction getCurrentInstruction();
    void decrementBurst();
    Memory::Block * getMemoryBlock();
    void setMemoryBlock(Memory::Block * block);
    int getCurrentBurst();
    void operator++();
    Process * getParent();
    int getLastQueue();
    void setLastQueue(int qNum);
    void addInstruction(std::string instr, bool toRandom);
    std::vector<Instruction> getInstructions();
    unsigned int getPid();
    void setName(std::string name);
    std::string getName();
    void setPid(int pid);
    void setPriority(int p);
    void setMemoryReq(int size);
    void setCycles(int cycles);
    void setPC(int pc);
    void incrementPC();
    PROCESS_STATE getState();
    void setState(PROCESS_STATE state);
    unsigned int getPriority();
    int getMemoryReq();
    int getCycles();
    int getProgramCounter();
};

#endif
