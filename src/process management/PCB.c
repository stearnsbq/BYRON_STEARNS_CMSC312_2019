#include <stdio.h>
#include "../structures/priorityqueue.h"
#include "../structures/queue.h"
#include "PCB.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    ProcessBlock *b = (ProcessBlock *)malloc(sizeof(ProcessBlock));
    FILE *f = fopen("../../tests/program1.txt", "r");
    if (f == NULL)
    {
        printf("file error");
        return -1;
    }

    char buf[40][14];
    int c;
    int lineNumber = 0;
    while (fgets(buf[lineNumber], 14, f))
    {
        if (strcmp(buf[lineNumber], "EXE") == 0)
        {
            //printf("%s", buf[lineNumber]);
            buildProcess(buf, lineNumber);
        }
        lineNumber++;
    }
}

ProcessBlock *buildProcess(char buffer[20][14], int size)
{
    int memory = atoi(buffer[0]);
    ProcessBlock *process = (ProcessBlock *)malloc(sizeof(ProcessBlock));
    process->memory = memory;
    process->state = NEW;
    process->pid = 425314;
    process->priority = 15;
    process->cycles = 0;
    process->pc = buffer[1];
    for (size_t i = 1; i < size; i++)
    {
        char *token = strtok(buffer[i], " ");
        token = strtok(NULL, " ");
        process->cycles += atoi(token);
    }
    printProcess(process);
}

void printProcess(ProcessBlock *p)
{
    printf("=======================\nProcess ID: %d\nState: %d\nPriority: %d\nMemory: %d\nCycles to complete: %d\nProgram Counter: %s (%p)\n=======================", p->pid, p->state, p->priority, p->memory, p->cycles, p->pc, p->pc);
}
