#ifndef MEMORY
#define MEMORY
#define MAX_SIZE 4398046511104 // 4096mb
#include <stdlib.h>
#include <fstream>
class Memory
{
public:
    class Block{
    public:
        Block();
        ~Block();
        void setNext(Block * next);
        void setSize(long long size);
        void setFree(bool free);
        Block * getNext();
        unsigned int getSize();
        bool isFree();
    private:
        Block * next;
        long long size;
        bool free;
    };
    Memory();
    Memory(long long sizeOfMemory);
    ~Memory();
    Block * alloc(long long size);
    void freeMemory(Block * blkPtr);
    void printBlocks();
    long long availableMemory();
    Block * getHead();

private:
    long long used;

    size_t maxMemory;
    Block *head;
    Block *tail;
    Block *findBestFit(long long size);
    Block *split(Block **block, long long size);
    void mergeFreeBlocks();
    std::ifstream page_out(Block **block);
    void page_in(std::ifstream page);
};

#endif
