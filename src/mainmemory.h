#ifndef MAINMEMORY_H
#define MAINMEMORY_H
#include <vector>
#include "PCB.hpp"
#include "pagetable.h"


class pagetable;
class mainmemory
{
public:
mainmemory(int totalMemory, double pageSize);
std::vector<page> allocateMemory(size_t size);
void freeMemory(std::vector<page> pages);
unsigned int getNextFrame();
unsigned int availableMemory();
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
std::vector<frame> emptyFrames;
std::vector<page *> TLB;
page * tlbSearch(int pageNum, int l, int h );

};

#endif // MAINMEMORY_H
