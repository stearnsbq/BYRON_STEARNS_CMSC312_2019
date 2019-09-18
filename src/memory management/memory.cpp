#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#define ALIGN(a) a + 7 - (a - 1) % 8

Memory::Block::Block()
{
}
Memory::Block::~Block()
{
    delete this;
}
Memory::Block::Block(size_t size)
{
    this->size = size;
    this->free = 1;
    this->end = NULL;
    this->next = NULL;
    this->start = NULL;
}

Memory::Memory()
{
}
Memory::Memory(size_t size)
{
    this->used = 0;
    this->maxMemory = ALIGN(size);
}

Memory::~Memory()
{
}

void *Memory::alloc(size_t size)
{
    if (size > this->maxMemory)
    {
        printf("Unable to allocate %d not enough memory on the device. Device has %d", size, this->maxMemory);
        return NULL;
    }

    if (!head)
    {
        this->head = new Block(this->maxMemory);
    }

    if (this->used + ALIGN(size) > this->maxMemory)
    {
        double percentage = ((double)this->used / (double)this->maxMemory) * 100.0;
        printf("Not enough memory! Trying to allocate %d when there is %d used of %d left (%.2f%% used) \n", ALIGN(size), this->used, this->maxMemory, percentage);
        return NULL;
    }
    else
    {
        this->used += ALIGN(size);
        Block *selected = findBestFit(size);

        return (split(&selected, size) + 1);
    }
}

Memory::Block *Memory::findBestFit(size_t size)
{

    size_t alignedSize = ALIGN(size);
    Block *cursor = this->head;
    Block *selected = this->head;
    while (cursor != NULL)
    {
        if (cursor->free && (cursor->size >= alignedSize && cursor->size < selected->size))
        {
            selected = cursor;
        }
        cursor = cursor->next;
    }
    return selected;
}

Memory::Block *Memory::split(Block **block, size_t size)
{
    size_t alignedSize = ALIGN(size);
    if (alignedSize >= (*block)->size)
    {
        (*block)->free = 0;
        return (*block);
    }
    Block *next = (*block)->next;
    if (!next)
    {
        Block *newBlock = new Block(sizeof(Block) + alignedSize);
        (*block)->size -= alignedSize;
        (*block)->next = newBlock;
        return newBlock;
    }
    else
    {
        Block *newBlock = new Block(sizeof(Block) + alignedSize);
        Block *next = (*block)->next;
        (*block)->size -= alignedSize;
        (*block)->next = newBlock;
        newBlock->next = next;

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
    Memory::Block *temp = this->head;
    Memory::Block **cursor = &head;
    while ((*cursor) != NULL)
    {
        if ((*cursor)->next && (*cursor)->free)
        {
            Memory::Block *next = (*cursor)->next->next;
            if (next)
            {
                (*cursor)->size += (*cursor)->next->size;
                Memory::Block *old = (*cursor)->next;
                delete (old);
                (*cursor)->next = next;
            }
            else
            {
                (*cursor)->size += (*cursor)->next->size;
                Memory::Block *old = (*cursor)->next;
                delete (old);
                (*cursor)->next = NULL;
            }
        }
        (*cursor) = (*cursor)->next;
    }
    head = temp;
}

void Memory::printBlocks()
{
    Block *cursor = this->head;
    while (cursor != NULL)
    {
        printf("===========\nSize %d\nFree %d\n\n===========\n", cursor->size, cursor->free);
        cursor = cursor->next;
    }
}

void Memory::page_in(FILE *page)
{
}

FILE *Memory::page_out(Block **block)
{
}

int main(int argc, char **argv)
{
    Memory *m = new Memory(10000000);
    void *ptr = m->alloc(1000);
    // void* ptr1 = m->alloc(1000);
    // void* ptr2 = m->alloc(1000);
    m->printBlocks();
}
