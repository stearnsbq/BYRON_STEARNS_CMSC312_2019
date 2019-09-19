#include <iostream>
#include <cstring>
#include "memory.h"
#define ALIGN(a) a + 7 - (a - 1) % 8

using namespace std;


Memory::Memory()
{
}

Memory::Memory(size_t size)
{
    this->used = 0;
    this->head = NULL;
    this->tail = NULL;
    this->maxMemory = ALIGN(size);
}

Memory::~Memory()
{
}

void *Memory::alloc(size_t size)
{
    size = ALIGN(size);
    if ((size + this->used) > this->maxMemory || size > this->maxMemory)
    {
        printf("NOT ENOUGH MEMORY");
        return NULL;
    }
    if (!this->head)
    {
        this->head = (Block *)malloc(sizeof(Block) + size);
        this->head->next = NULL;
        this->head->size = size;
        this->head->prev = NULL;
        this->head->free = 0;
        return this->head +1;
    }else{
        Block * selected = findBestFit(size);

        if (!selected)
        {
            selected = (Block *)malloc(sizeof(Block) + size);
            selected->free = 0;
            selected->size = size;
            selected->prev = NULL;
            selected->next = NULL;
        }

        if (!tail)
        {
            this->tail = selected;
            this->head->next = this->tail;
            this->tail->prev = this->head;
        }else if (selected == this->tail)
        {
            selected->free = 0;
        }else{
            this->tail->next = selected;
            selected->prev = this->tail;
            this->tail = selected;
        }

        return split(&selected, size)+1;   
    }

}

Memory::Block *Memory::findBestFit(size_t size)
{
    Block * cursor = this->head;
   while (cursor && !(cursor->free && cursor->size >= size)) {
    cursor = cursor->next;
  }
    return cursor;
}

Memory::Block *Memory::split(Block **block, size_t size)
{
    if ((*block)->size == size)
    {
        return (*block);
    }
    


    if ((*block) == this->tail)
    {
    Block * newBlock = (Block *)malloc(sizeof(Block) + size);
    newBlock->next = NULL;
    newBlock->prev = this->tail;
    newBlock->size = size;
    this->tail->size -= size;
    this->tail->next = newBlock; 
    this->tail->free = 1;  
    this->tail = newBlock;
    newBlock->free = 0;
    return newBlock;
    }else{
        Block * newBlock = (Block *)malloc(sizeof(Block) + size);
        newBlock->next = (*block)->next;
        newBlock->prev = (*block);
        newBlock->size = size;
        (*block)->size -= size;
        (*block)->next = newBlock;
        newBlock->free = 0;
    return newBlock;
    }
}




void Memory::freeMemory(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    Memory::Block *blockPtr = (Memory::Block *)ptr - 1;
    blockPtr->free = 1;
    mergeFreeBlocks();
}

void Memory::mergeFreeBlocks()
{
  
}

void Memory::printBlocks()
{
      Block *cursor = this->head;
    while (cursor != NULL)
    {
        printf("===========\nSize %d\nFree %d\n===========\n", cursor->size, cursor->free);
        cursor = cursor->next;
    }
}

void Memory::page_in(FILE *page)
{
}

FILE *Memory::page_out(Block **block)
{
    return NULL;
}

int main(int argc, char **argv)
{
    Memory *m = new Memory(4294967296);
    char *ptr1 = (char*)m->alloc(100);
   char *ptr3 = (char*)m->alloc(10000);
    m->freeMemory(ptr3);
    char *ptr4 = (char*)m->alloc(1000);
    char *ptr5 = (char*)m->alloc(2009);
    m->printBlocks();

}
