#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void addProcess(Heap **heap, ProcessBlock *newProcess)
{
    if (!(*heap))
    {
        printf("boddy1\n");
        (*heap) = (Heap *)malloc(sizeof(Heap));
        (*heap)->processes = (ProcessBlock *)malloc(INITIAL_SIZE * sizeof(ProcessBlock));
        (*heap)->used = 0;
        (*heap)->size = INITIAL_SIZE;
        (*heap)->processes[(*heap)->used++] = *newProcess;
    }
    else
    {
        printf("boddy2\n");
        if ((*heap)->size == (*heap)->used)
        {
            (*heap)->size *= 2;
            (*heap)->processes = (ProcessBlock *)realloc((*heap)->processes, (*heap)->size * sizeof(ProcessBlock));
        }
        (*heap)->processes[(*heap)->used++] = *newProcess;
        heapify(heap);
    }
}


void swap(ProcessBlock *x, ProcessBlock *y) 
{ 
    ProcessBlock  temp = *x; 
    *x = *y; 
    *y = temp; 
}



void print(Heap *heap){
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", heap->processes[i].priority);
    }
    
}


int parent(int i){
    return (i-1)/2;
}


void heapify(Heap** heap){
    int i = (*heap)->used - 1;
    while (i != 0 && (*heap)->processes[parent(i)].priority > (*heap)->processes[i].priority)
    {
        swap(&(*heap)->processes[i], &(*heap)->processes[parent(i)]);
        i = parent(i);
      
    }

}



void main(int argc, char **argv){
    Heap *heap = NULL;
    ProcessBlock *process1 = (ProcessBlock *)malloc(sizeof(ProcessBlock));
    process1->priority = 5;
    process1->state = NEW;
    process1->pid = 21451;
    ProcessBlock process2;
    process2.priority = 7;
    process2.state = NEW;
    process2.pid = 21452;
    ProcessBlock process3;
    process3.priority = 10;
    process3.state = NEW;
    process3.pid = 21453;
    ProcessBlock process4;
    process4.priority = 12;
    process4.state = NEW;
    process4.pid = 21454;
     ProcessBlock process5;
    process5.priority = 2;
    process5.state = NEW;
    process5.pid = 21454;
     ProcessBlock process6;
    process6.priority = 5;
    process6.state = NEW;
    process6.pid = 21454;
     ProcessBlock process7;
    process7.priority = 92;
    process7.state = NEW;
    process7.pid = 21454;
    addProcess(&heap, process1);
    addProcess(&heap, &process2);
    addProcess(&heap, &process3);
    addProcess(&heap, &process4);
    addProcess(&heap, &process5);
    addProcess(&heap, &process6);
    addProcess(&heap, &process7);
    print(heap);

}