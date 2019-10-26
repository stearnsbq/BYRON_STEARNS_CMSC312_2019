#ifndef CPU_H
#define CPU_H
#include "memory.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "scheduler.hpp"
#include <functional>

class CPU
{
private:
    std::vector<std::thread> threads;
    Scheduler * scheduler;
    Memory *memory;
    int clockTime;
    bool isRunning;
    int timeQuantum;
    std::thread clock_thread;
    void handler(int sig);
    void start();

public:
    CPU();
    ~CPU();
    void run();
    void setTimeQ(int time);
    int getTimeQ();
    Memory * getMemory();
    long long availableMemory();
    Memory::Block * allocateMemory(size_t amount);
    void freeMemory(Memory::Block * ptr);
};

extern CPU *cpu;

#endif
