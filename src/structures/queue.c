#include <stdio.h>
#include "queue.h"

void addProcess(Heap *heap, ProcessBlock newProcess)
{
    if (!heap)
    {
        heap->processes = (ProcessBlock *)malloc(INITIAL_SIZE * sizeof(ProcessBlock));
        heap->used = 0;
        heap->size = INITIAL_SIZE;
        heap->processes[heap->used++] = newProcess;
    }
    else
    {
        if (heap->size == heap->used)
        {
            heap->size *= 2;
            heap->processes = (ProcessBlock *)realloc(heap->processes, heap->size * sizeof(ProcessBlock));
        }
        heap->processes[heap->used++] = newProcess;
    }
}