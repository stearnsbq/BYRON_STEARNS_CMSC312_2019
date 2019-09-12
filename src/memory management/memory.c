#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#define ALIGN(a) a + 7 - (a - 1) % 8

Block *head = NULL;

void *alloc(size_t size)
{
    if (!head)
    {
        head = (Block *)malloc(sizeof(Block));
        head->size = 4096;
        head->free = 1;
        head->next = NULL;
    }
    Block *selected = findBestFit(size);
    return (split(&selected, size) + 1);
}

Block *findBestFit(size_t size)
{
    size_t alignedSize = ALIGN(size);
    Block *cursor = head;
    Block *selected = head;
    while (cursor != NULL)
    {
        if (cursor->free && cursor->size >= alignedSize)
        {
            selected = cursor;
        }
        cursor = cursor->next;
    }
    return selected;
}

Block *split(Block **block, size_t size)
{
    size_t alignedSize = ALIGN(size);
    if (alignedSize >= (*block)->size)
    {
        return (*block);
    }
    Block *next = (*block)->next;
    if (!next)
    {
        Block *newBlock = (Block *)malloc(sizeof(Block));
        newBlock->size = alignedSize;
        newBlock->free = 0;
        newBlock->next = NULL;
        (*block)->size -= alignedSize;
        (*block)->next = newBlock;
        return newBlock;
    }
    else
    {
        Block *newBlock = (Block *)malloc(sizeof(Block));
        Block *next = (*block)->next;
        newBlock->size = alignedSize;
        newBlock->free = 0;
        newBlock->next = NULL;
        (*block)->size -= alignedSize;
        (*block)->next = newBlock;
        newBlock->next = next;
        return newBlock;
    }
}

void freeMemory(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    Block *blockPtr = (Block *)ptr - 1;
    blockPtr->free = 1;
    mergeFreeBlocks();
}

void mergeFreeBlocks()
{
    Block *temp = head;
    Block **cursor = &head;
    while ((*cursor) != NULL)
    {
        if ((*cursor)->next && (*cursor)->free)
        {
            Block *next = (*cursor)->next->next;
            if (next)
            {
                (*cursor)->size += (*cursor)->next->size;
                (*cursor)->next = next;
            }
            else
            {
                (*cursor)->size += (*cursor)->next->size;
                (*cursor)->next = NULL;
            }
        }
        (*cursor) = (*cursor)->next;
    }
    head = temp;
}

void printBlocks()
{
    Block *cursor = head;
    while (cursor != NULL)
    {
        printf("===========\nSize %d\nFree %d\n", cursor->size, cursor->free);
        cursor = cursor->next;
    }
}

void page_in(FILE *page)
{
}

FILE *page_out(Block **block)
{
}

int main(int argc, char **argv)
{
    int *test1 = alloc(sizeof(int));
    int *test2 = alloc(sizeof(int));
    int *test3 = alloc(sizeof(int));
    int *test4 = alloc(sizeof(int));
    int *test5 = alloc(sizeof(int));

    freeMemory(test1);
    freeMemory(test2);
    freeMemory(test3);
    freeMemory(test4);
    freeMemory(test5);
    test5 = alloc(sizeof(int));
    freeMemory(test5);
    //printf("%d\n", head->size);
    //free(test);
    printBlocks();
}
