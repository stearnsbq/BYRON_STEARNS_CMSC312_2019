#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

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

void print(Heap *heap)
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

// void main(int argc, char **argv)
// {
//     Heap *heap = NULL;
//     ProcessBlock process1;
//     process1.priority = 1;
//     process1.state = NEW;
//     process1.pid = 21451;
//     ProcessBlock process2;
//     process2.priority = 2;
//     process2.state = NEW;
//     process2.pid = 21452;
//     ProcessBlock process3;
//     process3.priority = 3;
//     process3.state = NEW;
//     process3.pid = 21453;
//     ProcessBlock process4;
//     process4.priority = 4;
//     process4.state = NEW;
//     process4.pid = 21454;
//     ProcessBlock process5;
//     process5.priority = 5;
//     process5.state = NEW;
//     process5.pid = 21455;
//     ProcessBlock process6;
//     process6.priority = 6;
//     process6.state = NEW;
//     process6.pid = 21456;
//     ProcessBlock process7;
//     process7.priority = 7;
//     process7.state = NEW;
//     process7.pid = 21457;
//     ProcessBlock process8;
//     process8.priority = 8;
//     process8.state = NEW;
//     process8.pid = 21458;
//     ProcessBlock process9;
//     process9.priority = 9;
//     process9.state = NEW;
//     process9.pid = 21459;
//     ProcessBlock process10;
//     process10.priority = 10;
//     process10.state = NEW;
//     process10.pid = 21460;
//     ProcessBlock process11;
//     process11.priority = 11;
//     process11.state = NEW;
//     process11.pid = 21461;
//     addProcess(&heap, &process1);
//     addProcess(&heap, &process2);
//     addProcess(&heap, &process3);
//     addProcess(&heap, &process4);
//     addProcess(&heap, &process5);
//     addProcess(&heap, &process6);
//     addProcess(&heap, &process7);
//     addProcess(&heap, &process8);
//     addProcess(&heap, &process9);
//     addProcess(&heap, &process10);
//     //print(heap);
//     ProcessBlock t = removeProcess(&heap);
//     print(heap);
// }