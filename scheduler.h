struct Process {
unsigned int arrTime;
unsigned int reqTime;
unsigned int burstTime;
unsigned int pid;
struct Process* nextInQueue;
};