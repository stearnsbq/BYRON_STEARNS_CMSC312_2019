#ifndef MAINMEMORY_H
#define MAINMEMORY_H
#include <vector>
#include "PCB.hpp"

class mainmemory
{
public:
    mainmemory(int totalMemory, double pageSize);
    void allocateMemory(Process &process);
    void freeMemory(Process &process);
private:
    typedef struct {
        int num;
        bool free;
    }frame;
    int totalFrames;
    double pageSize;
    std::vector<frame> emptyFrames;
};

#endif // MAINMEMORY_H
