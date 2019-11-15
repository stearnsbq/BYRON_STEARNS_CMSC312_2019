#ifndef CPU_THREAD_H
#define CPU_THREAD_H
#include <thread>

class CPU_Thread
{
public:
CPU_Thread();
void executeOperation();
private:
bool isRunning;
};

#endif // CPU_THREAD_H
