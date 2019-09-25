#include "../structures/queue.hpp"
enum ALGORITHM
{
    ROUND_ROBIN,
    PRIORITY_SCHEDULING,
    MULTILEVEL_QUEUE,
};

class Scheduler
{
public:
    void addProcess(Process *Process);
    Process *getNextReadyProcess();

private:
    int timeQuantum;
    ALGORITHM algorithmToUse;
    Queue readyQueue;
};
