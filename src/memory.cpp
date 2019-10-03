#include <iostream>
#include "memory.hpp"
#define ALIGN(a) a + 7 - (a - 1) % 8


Memory::Memory()
{
    this->head = new Block();
    this->head->setSize(4398046511104);
    this->tail = this->head;
}


Memory::Memory(long long size)
{
    this->used = 0;
    this->maxMemory = size;
    this->head = new Block();
    this->head->setSize(ALIGN(size));
    this->tail = this->head;
}

Memory::~Memory()
{
}

Memory::Block * Memory::alloc(long long size)
{
    if((size + used) > MAX_SIZE || size > MAX_SIZE){
        return nullptr;
    }


}

Memory::Block *Memory::findBestFit(long long size)
{

}

Memory::Block *Memory::split(Block **block, long long size)
{
}

void Memory::freeMemory(Memory::Block * ptr)
{
    ptr->setFree(true);
    mergeFreeBlocks();
}

void Memory::mergeFreeBlocks()
{
}

void Memory::printBlocks()
{
}

void Memory::page_in(std::ifstream page)
{
}

std::ifstream Memory::page_out(Block **block)
{
}
