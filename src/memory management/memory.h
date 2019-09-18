#define MAX_MEMORY 4096
#ifndef MEMORY
#define MEMORY
class Memory
{
public:
    Memory();
    Memory(size_t sizeOfMemory);
    ~Memory();
    void *alloc(size_t size);
    void freeMemory(void *ptr);
    void printBlocks();

private:
    class Block
    {

    public:
        Block();
        Block(size_t size);
        ~Block();
        void *start;
        void *end;
        size_t size;
        int free;
        struct Block *next;
    };
    unsigned int used;
    size_t maxMemory;
    Block *head;
    Block *findBestFit(size_t size);
    Block *split(Block **block, size_t size);
    void mergeFreeBlocks();
    FILE *page_out(Block **block);
    void page_in(FILE *page);
};

#endif