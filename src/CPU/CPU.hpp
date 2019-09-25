#ifndef CPU_H
#define CPU_H
#include "../memory management/memory.hpp"
extern CPU *cpu;

class CPU
{
private:
    Memory memory;
public:
    void allocateMemory(size_t amount);
};

#endif