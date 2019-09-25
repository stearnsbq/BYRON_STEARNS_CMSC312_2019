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
    Scheduler();
    ~Scheduler();
    void addNewProcess(Process *Process);
    void addReadyProcess(Process *Process);
    Process *getNextReadyProcess();

private:
    void rotateProcess();
    void processNewQueue();
    void processReadyQueue();
    void processWaitingQueue();
    int timeQuantum;
    ALGORITHM algorithmToUse;
    Queue *readyQueue;
    Queue *newQueue;
    Queue *waitingQueue;
};
