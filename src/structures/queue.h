#include "../process management/PCB.h"
#ifndef QUEUE
#define QUEUE

class Queue
{
public:
    Queue();
    ~Queue();
    void enqueueProcess(ProcessBlock *data);
    ProcessBlock *dequeueProcess();
    void
    printList();

private:
    class Node
    {
    public:
        Node();
        Node(ProcessBlock *data);
        Node *getNext();
        ProcessBlock *getData();
        void setNext(Node *next);
        void setData(ProcessBlock *data);
        ~Node();

    private:
        Node *next;
        ProcessBlock *data;
    };
    Node *head;
    Node *tail;
    int count;
};

#endif