#include <vector>
#include "Process.h"
#ifndef PROCESSTABLE
#define PROCESSTABLE
class ProcessTable {
    private:
    std::vector<Process *> table;
    int hash(unsigned int pid);
    int currSize;
    int checkCollision(int index);
    double loadFactor;
    int storedItems;
    public:
    ProcessTable();
    ~ProcessTable();
    void put(Process *Process);
    Process * remove(unsigned int pid);
    int size();





}

#endif // DEBUG



