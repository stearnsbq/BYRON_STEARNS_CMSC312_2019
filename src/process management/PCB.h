#ifndef PCB
#define PCB
typedef enum PROCESS_STATE
{
    NEW,
    READY,
    RUN,
    WAIT,
    EXIT
} PROCESS_STATE;

typedef struct ProcessBlock
{
    unsigned int pid;
    PROCESS_STATE state;
    unsigned int priority;
    int memory;
    int cycles;
    char *pc;
} ProcessBlock;

ProcessBlock *buildProcess(char buffer[20][14], int size);
void printProcess(ProcessBlock *p);
#endif