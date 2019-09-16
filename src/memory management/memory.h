#define MAX_MEMORY 4096

typedef struct Block
{
    size_t size;
    size_t sizeOfData;
    int free;
    struct Block *next;
} Block;

void *alloc(size_t size, size_t sizeOfData);
void free(void *ptr);
Block *findBestFit(size_t size);
Block *split(Block **block, size_t size, size_t sizeofdata);
void mergeFreeBlocks();