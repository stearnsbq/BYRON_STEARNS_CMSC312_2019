#include <iostream>
#include "queue.h"

using namespace std;

Queue::Node::Node()
{
    this->next = NULL;
    this->data = NULL;
}
Queue::Node::Node(Process *data)
{
    this->next = NULL;
    this->data = data;
}
Queue::Node *Queue::Node::getNext()
{
    return this->next;
}
Process *Queue::Node::getData()
{
    return this->data;
}
void Queue::Node::setNext(Node *next)
{
    this->next = next;
}
void Queue::Node::setData(Process *data)
{
    this->data = data;
}
Queue::Node::~Node()
{
    delete next;
    delete data;
}

Queue::Queue()
{
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}
Queue::~Queue()
{
    while (this->head)
    {
        Node *tmp = this->head;
        delete tmp;
        this->head = this->head->getNext();
    }
}
void Queue::enqueueProcess(Process *data)
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
Process *Queue::dequeueProcess()
{
    if (!(this->head))
    {
        return NULL;
    }
    else if (!(this->tail))
    {
        Process *data = this->head->getData();
        Node *old = this->head;
        delete old;
        this->count--;
        return data;
    }
    else
    {
        Process *data = this->head->getData();
        Node *old = this->head;
        this->head = old->getNext();
        delete old;
        this->count--;
        return data;
    }
}
void Queue::printList()
{
    Node *cursor = head;
    while (cursor != NULL)
    {
        printf("DATA: %d\n", cursor->getData()->getPriority());
        cursor = cursor->getNext();
    }
}
