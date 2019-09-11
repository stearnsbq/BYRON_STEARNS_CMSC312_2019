#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void enqueueProcess(Queue **queue, ProcessBlock *data)
{
    if (!(*queue)->head) // empty
    {

        (*queue)->head = (Node *)malloc(sizeof(Node));
        (*queue)->tail = NULL;
        (*queue)->head->next = NULL;
        (*queue)->head->data = data;
        (*queue)->count++;
    }
    else if (!(*queue)->tail) // length 1
    {

        (*queue)->tail = (Node *)malloc(sizeof(Node));
        (*queue)->tail->data = data;
        (*queue)->tail->next = NULL;
        (*queue)->head->next = (*queue)->tail;
        (*queue)->count++;
    }
    else // whatever
    {

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        (*queue)->tail->next = newNode;
        (*queue)->tail = newNode;
        (*queue)->tail->next = NULL;

        (*queue)->count++;
    }
}

ProcessBlock *dequeueProcess(Queue **queue)
{
    if (!((*queue)->head))
    {
        return NULL;
    }
    else if (!((*queue)->tail))
    {
        ProcessBlock *data = (*queue)->head->data;
        Node *old = (*queue)->head;
        (*queue)->head = NULL;
        free(old);
        (*queue)->count--;
        return data;
    }
    else
    {
        ProcessBlock *data = (*queue)->head->data;
        Node *old = (*queue)->head;
        (*queue)->head = old->next;
        free(old);
        (*queue)->count--;
        return data;
    }
}

void printList(Queue **queue)
{
    Node *cursor = (*queue)->head;
    while (cursor != NULL)
    {
        printf("DATA: %d\n", cursor->data->priority);
        cursor = cursor->next;
    }
}