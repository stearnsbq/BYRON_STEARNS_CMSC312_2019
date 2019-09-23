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
  

}

Memory::Block *Memory::findBestFit(size_t size)
{
   
}

Memory::Block *Memory::split(Block **block, size_t size)
{
  
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
