
#include "priorityqueue.h"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
    this->heap.clear();
}

void PriorityQueue::addProcess(ProcessBlock *newProcess)
{

    this->heap.push_back(*newProcess);
    int i = getSize() - 1;

    while (i != 0 && this->heap[parent(i)].priority > this->heap[i].priority)
    {
        swap(&(this->heap[i]), &(this->heap[parent(i)]));
        i = parent(i);
    }
}

int PriorityQueue::getSize()
{
    return this->heap.size();
}

ProcessBlock PriorityQueue::removeProcess()
{
    ProcessBlock root = this->heap[0];
    PriorityQueue::heap[0] = this->heap.back();
    this->heap.pop_back();
    heapify(0);
    return root;
}

void PriorityQueue::swap(ProcessBlock *x, ProcessBlock *y)
{
    ProcessBlock temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueue::printPQueue()
{
    for (size_t i = 0; i < this->getSize(); i++)
    {
        printf("%d\n", this->heap.at(i).priority);
    }
}

int PriorityQueue::parent(int i)
{
    return (i - 1) / 2;
}

int PriorityQueue::left(int i)
{
    return 2 * i + 1;
}

int PriorityQueue::right(int i)
{
    return 2 * i + 2;
}

void PriorityQueue::heapify(int index)
{
    int l = left(index);
    int r = right(index);
    int i = index;
    if (l < this->getSize() && this->heap.at(l).priority < this->heap.at(index).priority)
    {
        i = l;
    }
    if (r < this->getSize() && this->heap.at(r).priority < this->heap.at(i).priority)
    {
        i = r;
    }
    if (i != index)
    {
        swap(&(this->heap[index]), &(this->heap[i]));
        heapify(i);
    }
}

