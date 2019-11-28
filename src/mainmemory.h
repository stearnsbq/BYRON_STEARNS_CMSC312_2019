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
unsigned int getNextFrame();
unsigned int availableMemory();
private:
typedef struct {
    unsigned int num;
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
page * tlbSearch(int pageNum, int l, int h );
std::mutex _mutex;

};

#endif // MAINMEMORY_H
