#ifndef PROCESS
#define PROCESS
typedef enum PROCESS_STATE
{
    NEW,
    READY,
    RUN,
    WAIT,
    EXIT
} PROCESS_STATE;



class Process{
    private:
    unsigned int pid;
    PROCESS_STATE state;
    unsigned int priority;
    int memory;
    int cycles;
    int *pc;
    public:
    Process();
    ~Process();
    unsigned int getPid();
    PROCESS_STATE getState();
    unsigned int getPriority();
    int getMemoryReq();
    int getCycles();
    int* getProgramCounter();
};





#endif // !1



