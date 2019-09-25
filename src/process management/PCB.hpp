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

class Process
{
private:
    unsigned int pid;
    PROCESS_STATE state;
    unsigned int priority;
    int memory;
    int cycles;
    int pc;

public:
    Process();
    ~Process();
    unsigned int getPid();
    void setPid(unsigned int pid);
    void setPriority(int p);
    void setMemoryReq(int size);
    void setCycles(int cycles);
    void setPC(int pc);
    PROCESS_STATE getState();
    void setState(PROCESS_STATE state);
    unsigned int getPriority();
    int getMemoryReq();
    int getCycles();
    int getProgramCounter();
};

#endif
