#include <iostream>
#include "queue.hpp"

using namespace std;

Queue::Node::Node()
{
    this->next = NULL;
}
Queue::Node::Node(Process data)
{
    this->next = NULL;
    this->data = data;
}

bool Queue::isEmpty()
{
    return count <= 0;
}

Queue::Node *Queue::Node::getNext()
{
    return this->next;
}
Process Queue::Node::getData()
{
    return this->data;
}
void Queue::Node::setNext(Node *next)
{
    this->next = next;
}
void Queue::Node::setData(Process data)
{
    this->data = data;
}
Queue::Node::~Node()
{
    this->next = NULL;
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

Process *Queue::peek()
{
    return &this->head->data;
}


void Queue::enqueueProcess(Process data)
{
    if (!(this->head)) // empty
    {
        this->head = new Node(data);
        this->tail = NULL;
        this->head->setNext(NULL);
        this->count++;
    }
    else if (!(this->tail)) // length 1
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
Process Queue::dequeueProcess()
{

    if (!this->head)
    {
      
    }
    else
    {
        this->tmp = *this->head;
        Process data = this->tmp.getData();
        delete(this->head);
        this->head = this->tmp.getNext();
        if (this->head == NULL)
        {
            this->tail = NULL;
        }
        this->count--;
        return data;
    }
}
void Queue::printList()
{
    Node *cursor = this->head;
    while (cursor != NULL)
    {
        std::cout << "DATA: " + cursor->getData().getCurrentInstruction().getBurst() << std::endl;
        cursor = cursor->getNext();
    }
}
