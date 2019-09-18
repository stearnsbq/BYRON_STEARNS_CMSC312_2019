#include <cstdlib>
#include <iostream>
#include "queue.h"

using namespace std;

class Queue
{
private:
    class Node
    {
    public:
        Node()
        {
            this->next = NULL;
            this->data = NULL;
        }
        Node(ProcessBlock *data)
        {
            this->next = NULL;
            this->data = data;
        }
        Node *getNext()
        {
            return this->next;
        }
        ProcessBlock *getData()
        {
            return this->data;
        }
        void setNext(Node *next)
        {
            this->next = next;
        }
        void setData(ProcessBlock *data)
        {
            this->data = data;
        }
        ~Node()
        {
            delete next;
            delete data;
        }

    private:
        Node *next;
        ProcessBlock *data;
    };
    Node *head;
    Node *tail;
    int count;

public:
    Queue()
    {
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
    }
    ~Queue()
    {
        while (this->head)
        {
            Node *tmp = this->head;
            delete tmp;
            this->head = this->head->getNext();
        }
    }
    void enqueueProcess(ProcessBlock *data)
    {
        if (!this->head) // empty
        {
            this->head = new Node(data);
            this->tail = NULL;
            this->head->setNext(NULL);
            this->count++;
        }
        else if (!this->tail) // length 1
        {
            this->tail = new Node(data);
            this->tail->setNext(NULL);
            this->head->setNext(tail);
            this->count++;
        }
        else // whatever
        {
            Node *newNode = new Node(data);
            this->tail->setNext(newNode);
            this->tail = newNode;
            this->tail->setNext(NULL);

            this->count++;
        }
    }
    ProcessBlock *dequeueProcess()
    {
        if (!(this->head))
        {
            return NULL;
        }
        else if (!(this->tail))
        {
            ProcessBlock *data = this->head->getData();
            Node *old = this->head;
            this->head = NULL;
            delete old;
            this->count--;
            return data;
        }
        else
        {
            ProcessBlock *data = this->head->getData();
            Node *old = this->head;
            this->head = old->getNext();
            delete old;
            this->count--;
            return data;
        }
    }
    void
    printList()
    {
        Node *cursor = this->head;
        while (cursor != NULL)
        {
            printf("DATA: %d\n", cursor->getData()->priority);
            cursor = cursor->getNext();
        }
    }
};

int main(void)
{
    ProcessBlock pb;
    pb.priority = 1;
    ProcessBlock pb1;
    pb1.priority = 2;
    ProcessBlock pb2;
    pb2.priority = 3;
    Queue *q = new Queue();
    q->enqueueProcess(&pb);
    q->enqueueProcess(&pb1);
    q->enqueueProcess(&pb2);
    q->printList();
}
