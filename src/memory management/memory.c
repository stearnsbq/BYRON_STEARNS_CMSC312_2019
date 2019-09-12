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
        head->free = 0;
        head->next = NULL;
    }
    Block *selected = findBestFit(size);
    return (split(selected, size) + 1);
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

void free(void *ptr)
{
    if (!ptr)
    {
        return;
    }
    Block *blockPtr = (Block *)ptr - 1;
    blockPtr->free = 1;
}

FILE *page_out(Block **block)
{
}

void page_in(FILE *page)
{
}