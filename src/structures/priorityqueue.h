#include "../process management/PCB.h"
#include <vector>
#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

class PriorityQueue
{
private:
    std::vector<ProcessBlock> heap;
    int size;
    void heapify(int index);
    int left(int i);
    int right(int i);
    int parent(int i);
    void swap(ProcessBlock *x, ProcessBlock *y);

public:
    PriorityQueue();
    ~PriorityQueue();
    void addProcess(ProcessBlock *data);
    ProcessBlock removeProcess();
    void printPQueue();
    int getSize();
};

// prints out the heap
#endif