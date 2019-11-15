#ifndef CORE_H
#define CORE_H
#include <stack>
#include <thread>
#include <CPU.hpp>
#include <cpu_thread.h>

class Core
{
public:
Core();
void run();
private:
ShortTermScheduler * scheduler;


};

#endif // CORE_H
