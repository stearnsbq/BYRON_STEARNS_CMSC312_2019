#ifndef MAIN_HPP
#define MAIN_HPP
#include "CPU/CPU.hpp"
#include "Scheduler/scheduler.hpp"

class Main
{
private:
    CPU cpu;
    Scheduler scheduler;

public:
    Main();
    ~Main();
};

#endif