#ifndef PCU
#define PCU
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
} ProcessBlock;

#endif