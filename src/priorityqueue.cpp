
#include "priorityqueue.hpp"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
    this->heap.clear();
}

void PriorityQueue::addProcess(Process *newProcess)
{

    this->heap.push_back(newProcess);
    int i = getSize() - 1;

    while (i != 0 && this->heap[parent(i)]->getPriority() > this->heap[i]->getPriority())
    {
        swap((this->heap[i]), (this->heap[parent(i)]));
        i = parent(i);
    }
}

int PriorityQueue::getSize()
{
    return this->heap.size();
}

Process *PriorityQueue::removeProcess()
{
    Process *root = this->heap[0];
    PriorityQueue::heap[0] = this->heap.back();
    this->heap.pop_back();
    heapify(0);
    return root;
}

void PriorityQueue::swap(Process *x, Process *y)
{
    Process temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueue::printPQueue()
{
    for (size_t i = 0; i < this->getSize(); i++)
    {
        printf("%d\n", this->heap.at(i)->getPriority());
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
    if (l < this->getSize() && this->heap.at(l)->getPriority() < this->heap.at(index)->getPriority())
    {
        i = l;
    }
    if (r < this->getSize() && this->heap.at(r)->getPriority() < this->heap.at(i)->getPriority())
    {
        i = r;
    }
    if (i != index)
    {
        swap((this->heap[index]), (this->heap[i]));
        heapify(i);
    }
}
