#ifndef QUEUE
#define QUEUE
#include "PCB.hpp"
#include <queue>

template <typename T>
class Queue
{
public:

Queue();
~Queue();
void push();
void pop();
T top();
bool empty();
int size();
private:
std::queue<T> queue;


};


#endif
