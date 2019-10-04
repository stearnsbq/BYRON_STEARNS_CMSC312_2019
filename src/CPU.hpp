#ifndef CPU_H
#define CPU_H
#include "memory.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

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
    void clockThread(std::function<void ()> func);

public:
    CPU();
    ~CPU();
    void clock(std::function<void ()> func);
    void setTimeQ(int time);
    int getTimeQ();
    Memory * getMemory();
    long long availableMemory();
    Memory::Block * allocateMemory(size_t amount);
    void freeMemory(Memory::Block * ptr);
};

extern CPU *cpu;

#endif
