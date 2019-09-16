#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#define ALIGN(a) a + 7 - (a - 1) % 8

Block *head = NULL;
size_t usedMemory = 0;

void *alloc(size_t size, size_t sizeOfData)
{
    if (size > MAX_MEMORY)
    {
        printf("Unable to allocate %d not enough memory on the device. Device has %d", size, MAX_MEMORY);
        return NULL;
    }

    if (!head)
    {
        head = (Block *)malloc(sizeof(Block));
        head->size = 4096;
        head->sizeOfData = 0;
        head->free = 1;
        head->next = NULL;
    }

    if (usedMemory + ALIGN(size) > MAX_MEMORY)
    {
        double percentage = ((double)usedMemory / (double)MAX_MEMORY) * 100.0;
        printf("Not enough memory! Trying to allocate %d when there is %d used of %d left (%.2f%% used) \n", ALIGN(size), usedMemory, MAX_MEMORY, percentage);
        return NULL;
    }
    else
    {
        usedMemory += ALIGN(size);
        Block *selected = findBestFit(size);
        selected->sizeOfData = sizeOfData;
        return (split(&selected, size, sizeOfData) + 1);
    }
}

Block *findBestFit(size_t size)
{

    size_t alignedSize = ALIGN(size);
    Block *cursor = head;
    Block *selected = head;
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

Block *split(Block **block, size_t size, size_t sizeofdata)
{
    size_t alignedSize = ALIGN(size);
    if (alignedSize >= (*block)->size)
    {
        (*block)->free = 0;
        (*block)->sizeOfData = sizeofdata;
        return (*block);
    }
    Block *next = (*block)->next;
    if (!next)
    {
        Block *newBlock = (Block *)malloc(sizeof(Block) + alignedSize);
        newBlock->size = alignedSize;
        newBlock->free = 0;
        newBlock->next = NULL;
        newBlock->sizeOfData = sizeofdata;
        (*block)->size -= alignedSize;
        (*block)->next = newBlock;
        return newBlock;
    }
    else
    {
        Block *newBlock = (Block *)malloc(sizeof(Block) + alignedSize);
        Block *next = (*block)->next;
        newBlock->size = alignedSize;
        newBlock->free = 0;
        newBlock->next = NULL;
        newBlock->sizeOfData = sizeofdata;
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
                Block *old = (*cursor)->next;
                free(old);
                (*cursor)->next = next;
            }
            else
            {
                (*cursor)->size += (*cursor)->next->size;
                Block *old = (*cursor)->next;
                free(old);
                (*cursor)->next = NULL;
            }
        }
        (*cursor) = (*cursor)->next;
    }
    head = temp;
    head->sizeOfData = 0;
}

void printBlocks()
{
    Block *cursor = head;
    while (cursor != NULL)
    {
        printf("===========\nSize %d\nFree %d\nSizeof: %d\n===========\n", cursor->size, cursor->free, cursor->sizeOfData);
        cursor = cursor->next;
    }
}

void page_in(FILE *page)
{
}

FILE *page_out(Block **block)
{
    FILE *page = fopen("p1.page", "ab+");

    fwrite((*block) + 1, (*block)->sizeOfData, (*block)->size, page);
}

int main(int argc, char **argv)
{
    char *test1 = (char *)alloc(100, 1);
    test1[0] = 'b';
    test1[1] = 'o';
    test1[2] = 'b';
    test1[3] = 'b';
    test1[4] = 'y';
    test1[5] = '\0';
    page_out(&(head->next));
    printf("%s\n", test1);
    //freeMemory(test1);
    printBlocks();
}
