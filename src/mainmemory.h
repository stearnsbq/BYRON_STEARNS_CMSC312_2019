#ifndef MAINMEMORY_H
#define MAINMEMORY_H
#include <vector>
#include "PCB.hpp"
#include "pagetable.h"
#include <stack>
#include <mutex>


class pagetable;
class mainmemory
{
public:
mainmemory(unsigned int totalMemory, double pageSize);
std::vector<page> allocateMemory(size_t size);
void freeMemory(std::vector<page> pages);
int getNextFrame();
unsigned int availableMemory();
void setPagesDirty(std::vector<page>& pages);
private:
typedef struct {
    int num;
    bool free;
}frame;
unsigned nextFrame;
unsigned int usedFrames;
pagetable * pageTable;
int totalFrames;
unsigned int totalMemory;
double pageSize;
std::stack<frame> emptyFrames;
std::vector<frame> frames;
std::vector<page *> TLB;
std::mutex _mutex;

};

#endif // MAINMEMORY_H
