#include "../process management/PCU.h"
#define INITIAL_SIZE 10
#ifndef QUEUE
#define QUEUE
typedef struct Heap
{
    ProcessBlock *processes;
    int size;
    int used;
} Heap;

void addProcess(Heap **heap, ProcessBlock *data); // adds a process to the priority queue
ProcessBlock removeProcess(Heap **heap);          // removes the highest priority process and returns it
ProcessBlock *getMin(Heap *heap);                 // returns a pointer to highest priority process
void heapify(Heap **heap, int index);             // make sure the heap doesn't violate min heap property
void swap(ProcessBlock *x, ProcessBlock *y);      // swaps in place
int left(int i);
int right(int i);
int parent(int i);
#endif