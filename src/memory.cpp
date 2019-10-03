#include <iostream>
#include "memory.hpp"
#define ALIGN(a) a + 7 - (a - 1) % 8


Memory::Memory()
{
    this->head = new Block();
    this->head->setSize(4398046511104);
    this->head->setFree(true);
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

long long Memory::availableMemory(){
    return MAX_SIZE - used;
}

Memory::Block * Memory::getHead(){
    return this->head;
}

Memory::Block * Memory::alloc(long long size)
{
    if((size + used) > MAX_SIZE || size > MAX_SIZE){
        return nullptr;
    }
    Block * bestFit = this->findBestFit(ALIGN(size));
    used += ALIGN(size);
    return this->split(&bestFit, ALIGN(size));
}

Memory::Block *Memory::findBestFit(long long size)
{
    Block * bestFit = this->head;
    Block * cursor = this->head;
    while(cursor){
        if(cursor->isFree() && cursor->getSize() < bestFit->getSize() && bestFit->getSize() >= size){
            bestFit = cursor;
        }
        cursor = cursor->getNext();
    }

    return bestFit;
}

Memory::Block *Memory::split(Block **block, long long size)
{
    if((*block)->getSize() == size){
        return *block;
    }

   if((*block) == this->tail){
    Block * newBlock = new Block();
    newBlock->setSize(size);
    newBlock->setFree(false);
    (*block)->setSize((*block)->getSize() - size);
    (*block)->setNext(newBlock);
    this->tail = newBlock;
    return newBlock;
   }else{
    Block * newBlock = new Block();
    newBlock->setSize(size);
    newBlock->setFree(false);
    Block * next = (*block)->getNext();
    (*block)->setSize((*block)->getSize() - size);
    (*block)->setNext(newBlock);
    newBlock->setNext(next);
    return newBlock;
   }
}

void Memory::freeMemory(Block * ptr)
{
    ptr->setFree(true);
    mergeFreeBlocks();
}

void Memory::mergeFreeBlocks()
{
    Block *temp = head;
     Block **cursor = &head;
     while ((*cursor))
     {
         if ((*cursor)->getNext() && (*cursor)->isFree())
         {
             Block *next = (*cursor)->getNext()->getNext();
             if (next)
             {
                 (*cursor)->setSize( (*cursor)->getSize() + (*cursor)->getNext()->getSize());
                 (*cursor)->setNext(next);
             }
             else
             {
                 (*cursor)->setSize( (*cursor)->getSize() + (*cursor)->getNext()->getSize());
                 (*cursor)->setNext(nullptr);
             }
         }
         (*cursor) = (*cursor)->getNext();
     }
     head = temp;
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


Memory::Block::Block(){
    this->free = true;
    this->size = 0;
    this->next = nullptr;

}
Memory::Block::~Block(){

}
void Memory::Block::setNext(Block * next){
    this->next = next;
}
void Memory::Block::setSize(long long size){
    this->size = size;
}
void Memory::Block::setFree(bool free){
    this->free = free;
}

Memory::Block * Memory::Block::getNext(){
   return this->next;
}
unsigned int Memory::Block::getSize(){
return this->size;
}
bool Memory::Block::isFree(){
    return this->free;
}













