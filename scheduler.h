struct Process {
unsigned int arrTime;
unsigned int reqTime;
unsigned int burstTime;
unsigned int pid;
struct Process* nextInQueue;
};


void enqueueProcess(unsigned int pid);
struct Process dequeueProcess();
void runProcess(struct Process* nextToRun);