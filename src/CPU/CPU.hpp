#ifndef CPU_H
#define CPU_H
#include "../memory management/memory.hpp"
#include <chrono>
#include <thread>
#include <vector>

class CPU
{
private:
    std::vector<std::thread> threads;
    Memory *memory;
    int clockTime;
    bool isRunning;
    int timeQuantum;
    std::thread clock_thread;
    void handler(int sig);
    template <typename Function>
    void clockThread(Function func);

public:
    CPU();
    ~CPU();
    template <typename Function>
    void clock(Function func);
    void setTimeQ(int time);
    int getTimeQ();
    int availableMemory();
    void allocateMemory(size_t amount);
};

extern CPU *cpu;

#endif