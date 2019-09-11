#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityqueue.h"

void addProcess(Heap **heap, ProcessBlock *newProcess)
{
    if (!(*heap)) // if heap is null create the structure
    {
        (*heap) = (Heap *)malloc(sizeof(Heap));
        (*heap)->processes = (ProcessBlock *)calloc(INITIAL_SIZE, sizeof(ProcessBlock));
        (*heap)->used = 0;
        (*heap)->size = INITIAL_SIZE;
        (*heap)->processes[(*heap)->used++] = *newProcess;
    }
    else
    {

        if ((*heap)->size == (*heap)->used) // dynamically resizes the heap
        {
            int oldSize = (*heap)->size;
            (*heap)->size *= 2;
            (*heap)->processes = (ProcessBlock *)realloc((*heap)->processes, (*heap)->size * sizeof(ProcessBlock));
            memset(&(*heap)->processes[oldSize], -1, oldSize * sizeof(ProcessBlock));
        }
        (*heap)->processes[(*heap)->used++] = *newProcess;

        int i = (*heap)->used - 1;
        while (i != 0 && (*heap)->processes[parent(i)].priority > (*heap)->processes[i].priority)
        {
            swap(&(*heap)->processes[i], &(*heap)->processes[parent(i)]);
            i = parent(i);
        }
    }
}

ProcessBlock removeProcess(Heap **heap)
{
    ProcessBlock root = (*heap)->processes[0];
    (*heap)->processes[0] = (*heap)->processes[(*heap)->used - 1];
    (*heap)->used--;
    (*heap)->processes[(*heap)->used].priority = -1;
    heapify(heap, 0);
    root.state = RUN;
    return root;
}

void swap(ProcessBlock *x, ProcessBlock *y)
{
    ProcessBlock temp = *x;
    *x = *y;
    *y = temp;
}

void printPQueue(Heap *heap)
{
    for (size_t i = 0; i < heap->size; i++)
    {
        printf("%d\n", heap->processes[i].priority);
    }
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

ProcessBlock *getMin(Heap *heap)
{
    return &heap->processes[0];
}

void heapify(Heap **heap, int index)
{
    int l = left(index);
    int r = right(index);
    int i = index;
    if (l <= (*heap)->used && (*heap)->processes[l].priority <= (*heap)->processes[index].priority)
    {
        i = l;
    }
    if (r <= (*heap)->used && (*heap)->processes[r].priority <= (*heap)->processes[i].priority)
    {
        i = r;
    }
    if (i != index)
    {
        swap(&(*heap)->processes[index], &(*heap)->processes[i]);
        heapify(heap, i);
    }
}
