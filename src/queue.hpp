#ifndef QUEUE
#define QUEUE
#include "PCB.hpp"
class Queue
{
public:
    Queue();
    ~Queue();
    void enqueueProcess(Process data);
    Process dequeueProcess();
    void printList();
    Process peek();
    bool isEmpty();

private:
    class Node
    {
    public:
        Node();
        Node(Process data);
        Node *getNext();
        Process getData();
        void setNext(Node *next);
        void setData(Process data);
        ~Node();

    private:
        Node *next;
        Process data;
    };
    Node *head;
    Node *tail;
    Node tmp;
    int count;
};

#endif
