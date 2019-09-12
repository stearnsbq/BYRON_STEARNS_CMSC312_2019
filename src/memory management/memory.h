#define MAX_MEMORY 4096

typedef struct Block
{
    size_t size;
    // void *data;
    int free;
    struct Block *next;
} Block;

void *alloc(size_t size);
void free(void *ptr);
Block *findBestFit(size_t size);
Block *split(Block **block, size_t size);
void mergeFreeBlocks();