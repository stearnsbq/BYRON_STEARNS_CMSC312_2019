#include "Process.hpp"
#ifndef QUEUE
#define QUEUE

class Queue
{
public:
    Queue();
    ~Queue();
    void enqueueProcess(Process *data);
    Process *dequeueProcess();
    void
    printList();

private:
    class Node
    {
    public:
        Node();
        Node(Process *data);
        Node *getNext();
        Process *getData();
        void setNext(Node *next);
        void setData(Process *data);
        ~Node();

    private:
        Node *next;
        Process *data;
    };
    Node *head;
    Node *tail;
    int count;
};

#endif