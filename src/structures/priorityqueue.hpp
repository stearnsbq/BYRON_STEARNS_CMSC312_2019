#include "Process.hpp"
#include <vector>
#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

class PriorityQueue
{
private:
    std::vector<Process *> heap;
    int size;
    void heapify(int index);
    int left(int i);
    int right(int i);
    int parent(int i);
    void swap(Process *x, Process *y);

public:
    PriorityQueue();
    ~PriorityQueue();
    void addProcess(Process *data);
    Process *removeProcess();
    void printPQueue();
    int getSize();
};

// prints out the heap
#endif