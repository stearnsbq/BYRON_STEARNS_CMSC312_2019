#ifndef PROCESS
#define PROCESS
#include <string>
#include <vector>
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
    std::string name;
    std::vector<std::string> instructions[];
    PROCESS_STATE state;
    unsigned int priority;
    int memory;
    int cycles;
    int pc;

public:
    Process();
    ~Process();
    void operator++();
    unsigned int getPid();
    void setName(std::string name);
    std::string getName();
    void setPid(unsigned int pid);
    void setPriority(int p);
    void setMemoryReq(int size);
    void setCycles(int cycles);
    void setPC(int pc);
    void incrementPC();
    PROCESS_STATE getState();
    void setState(PROCESS_STATE state);
    unsigned int getPriority();
    int getMemoryReq();
    int getCycles();
    int getProgramCounter();
};

#endif
