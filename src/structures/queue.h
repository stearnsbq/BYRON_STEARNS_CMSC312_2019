#include "../process management/PCU.h"
#define INITIAL_SIZE 10
typedef struct Heap
{
    ProcessBlock *processes;
    int size;
    int used;
} Heap;

void addProcess(Heap **heap, ProcessBlock *data); // adds a process to the priority queue
void removeProcess(Heap *heap);                 // removes the highest priority process
ProcessBlock *highest(Heap *heap);              // returns a pointer to highest priority process
ProcessBlock *lowest(Heap *heap);               // returns a pointer to the lowest priority process
void heapify(Heap **heap); // make sure the heap doesn't violate min heap property
void swap(ProcessBlock *x, ProcessBlock *y); // swaps in place