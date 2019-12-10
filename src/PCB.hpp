#ifndef PROCESS
#define PROCESS
#include <vector>
#include <iostream>
#include <string>
#include "instruction.hpp"
#include <QString>
#include <QJsonObject>
#include "page.h"

typedef enum PROCESS_STATE
{
    NEW,
    READY,
    RUN,
    WAIT,
    EXIT,
    WAITING_FOR_CHILD,
    WAITING_FOR_MSG,
} PROCESS_STATE;

class Process
{
private:
unsigned int pid;
std::string name;
std::vector<Instruction> instructions;
Process * parent;
Process * child;
Instruction currInstr;
PROCESS_STATE state;
int priority;
int cycles = -1;
int pc;
int memory;
int lastQueue;

public:
Process();
Process(Process * parent);
~Process();
bool operator<( Process const& p2) const;
std::vector <page> pages;
Instruction getCurrentInstruction();
void decrementBurst();
int getCurrentBurst();
void operator++();
Process * getParent();
int getLastQueue();
void setLastQueue(int qNum);
QString getStateString();
TYPE getCurrentInstructionType();
void addInstruction(QJsonObject instr,  bool toRandom);
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
void setChild(Process * child);
Process * getChild();
void setParent(Process * parent);
PROCESS_STATE getState();
void setState(PROCESS_STATE state);
int getPriority();
int getMemoryReq();
int getCycles();
int getProgramCounter();
QString toString();
};

#endif
