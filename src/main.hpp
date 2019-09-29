#ifndef MAIN_HPP
#define MAIN_HPP
#include "CPU.hpp"
#include "scheduler.hpp"

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
